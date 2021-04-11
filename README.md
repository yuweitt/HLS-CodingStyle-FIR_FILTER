# HLS-Coding-Style-Decimation-Interpolation-Multi-stage-FIR
HLS Coding Style Decimation/Interpolation/Multi-stage FIR
###### tags: `高等計算機結構_paper summary`

# LAB_A
## Using Decimation in Filters(在過濾器中使用抽取)

抽取(Decimation)或丟棄樣本(Down sampling)用於降低信號的採樣率。 這是通過定期丟棄足夠的樣本以匹配所需的速率降低來完成的。  M的減少意味著保留每個Mth的樣本，然後丟棄其餘的樣本。 但是，由於頻率混合重疊，通常不可能簡單地丟棄數據。 隨著採樣率的降低，採樣信號的複制頻譜會聚在一起並在某個點重疊，從而使信號無法使用。 為了防止這種情況發生，必須對信號進行低通濾波(Lowpass)以防止混疊。 通過將Lowpass FIR濾波器與Down sampling功能結合使用，可以使FIR以較低的dara rate工作，從而減小了面積。 使用C++設計抽取器有兩種方法。 一種是將算法代碼與循環流水線一起使用以獲得所需的向下採樣率，另一種是根據向下採樣的數據率將資源共享手動編碼到C++中。

## Algorithmic Decimation(算法抽取)
在進行更抽象的編碼時，設計高效的抽取濾波器的關鍵是確保以較低的down sample對設計進行pipeline的處理，同時以原始速率讀取數據。 這樣可以安排在多個時鐘週期之間共享操作，從而最大程度地減少了面積。 示例155顯示了抽取濾波器的模板化實現。 讀者在這一點上應該熟悉模板化，它允許構建高度可重用的設計。 此處介紹的抽取FIR也將在以後的部分中使用。

```cpp
#include <ac_fixed.h>
#include <ac_channel.h>
#include "shift_class.h"
template<int W0, int W1, int N>
struct _WN{
enum { val = W0 + W1 + ac::log2_ceil<N>::val };
};
template<int ID, 
int W0, int I0, 
int W1, int I1,
int N, int RATE>
#pragma hls_design block
void dec(ac_channel<ac_fixed<W0,I0> > &x, 
ac_fixed<W1,I1> h[N], 
ac_channel<ac_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> > &y){
static shift_class<ac_fixed<W0,I0>,N> regs;
ac_fixed<_WN<W0,W1,N>::val,_WN<I0,I1,N>::val> acc = 0;
ac_fixed<W0,I0> x_int;

if (x.available(2)){
READ:for(int i=0;i<RATE;i++)
    x_int = x.read();
regs << x_int;
MAC:for (int i = 0; i<N; i++) {
acc += h[i]*regs[i];
}
y.write(acc);
}
}

```
第4到7行-創建了一個輔助結構，以計算output和內部累加器數據類型的整數和小數位數。 假設所需的位數等於輸入位數的總和加上基於抽頭數量N的log2位數的增長
第8到11行-功能模板參數允許指定輸入數據以及係數固定點的寬度和符號，Tap數:N和decimation rate:RATE。創建函數的多個instance需要ID參數。
int ID : 每個instance都有自己的一個ID
int W : input 總寬度
int I : input 中整數的寬度(意思就是浮點數的寬度就等於W-I)
int N : tap數(N=4表示此FIR用到4個歷史data)
int RATE : decimation rate
第14和16行-輔助結構_WN用於計算輸出和內部累加器所需的位數。
第18和19行-應該在函數調用的開始讀取輸入數據。 讀取RATE倍率，其中RATE是抽取率。READ循環應完全展開。 如果頂層設計使用II = RATE進行pipeline化，則在scheduling期間會分散輸入的RATE讀取，從而可以共享資源。
第24行-如果採用II=RATE方式進行pipeline設計，則每個RATE的clock cycle都會發生write of the output


## Manual Decimation(手動抽取)
8bit data & coefficients
4 filter taps
decimation rate = 2

```cpp
#include <ac_channel.h>
#include "shift_class.h"
#include "fir_filter.h"
#include "decimate.hpp"
void fir_filter(ac_channel<ac_fixed<8,1> > &x,ac_fixed<8,1> h[4],
                ac_channel<ac_fixed<18,4> > &y){
    dec<0,8,1,8,1,4,2>(x,h,y);
}

```

• All IO mapped to wire enable interfaces
• IO input rate=1 sample/clock
• All arrays mapped to registers
• Main loop pipelined with II=2
• All loops fully unrolled

圖145顯示了example 156的大致時間表以及上面列出的限制。 時間表顯示可以基於II在時間表上分配四個filter taps的乘法，在這種情況下僅需要兩個乘法器。 對於此設計示例，II被設置為等於2，因為濾波器的抽取率將-2，並且input data rate=1。 通常，應將II設置為等於輸出數據速率，可以將其計算為：
Output Rate = Input Rate * Decimation Rate
![](https://i.imgur.com/CDbwLRs.png)

注意：讀取多個input並以output rate進行pipeline處理僅適用於single block decimation。如果設計在同一層次的block中包含多個decimation filters，則需要一種不同的方法，該方法將在後面的部分中介紹。


前面的範例顯示了如何使用pipeline從簡單的FIR描述中合成filter。 當II大於1時，HLS自動能夠共享資源。 也可以將資源共享直接編碼到decimation filter中。 儘管需要更多的精力，但在設計single block的muti-stage decimation時，它可能會在較小的面積方面帶來一些好處。
但是，與幾乎不需要了解抽取機制的high-level example不同，低級實現要求我們了解如何處理數據。 關鍵是要了解數據如何通過tap shift register以及何時由filter產生output data。
   通過example 157中所示的純算法實現，可以最好地理解這一點。由於每個函數調用只能讀取一個值，因此該example必須以input rate進行pipeline處理。 每隔一個調用有條件地寫入output。 這可能是一種低效的實現方式，因為當“ cnt”等於1時需要完整的MAC(Multiplier-Accumulator)計算，並且以intput rate對它進行pipeline處理。當“cnt”等於零時，數據將被移位。
   

```cpp
#include <ac_channel.h>
#include <ac_fixed.h>
#include "shift_class.h"
void dec2(ac_channel< ac_fixed<8,1> > &x,
          ac_fixed<8,1> h[4],
          ac_channel< ac_fixed<19,4> > &y){
  static shift_class<ac_fixed<8,1>,4> regs;
  ac_fixed<19,8> temp = 0;
  static ac_int<1,0> cnt;
  
  regs << x.read();
  MAC:for (int i = 0; i<4; i++) {
  temp += h[i]*regs[i];
  }
  if(cnt==1)//Phase 1
  y.write(temp);
  cnt++;
}

```
圖146顯示了example157中兩次調用該函數的tap shift register的內容。
   用M進行抽取會產生M個階段，每M-1個階段將丟棄輸出，而一個階段將計算並寫出輸出。由於丟棄階段僅轉移數據，因此將計算分配到所有階段似乎是一個好主意，從而減少了所需乘法器和加法器的總數。 當pipeline的II大於1時，這就是調度可以自動執行的操作
![](https://i.imgur.com/I2iKACa.png)
The filter computation of y[n] in Phase 1 is:
Phase1: y[5]=h[0]*regs[0]+h[1]*regs[1]+h[2]*regs[2]+h[3]*regs[3]
可以將其重寫以計算Pase:0中最後兩個tap的相乘和累加。從tap shift register中讀取tap data，以解決各phase之間的位置差異。
Phase 0: temp=h[2]*regs[1]+h[3]*regs[2]
Thus:
Phase1: y[5]=h[0]*regs[0]+h[1]*regs[1]+temp

example 158給出了一個4 tap decimation filter，該filter手動編碼跨clock cycle的共享。 假設此example的input data rate為每個clock一個採樣。 與example 155不同，此example使用II = 1進行pipeline處理，並根據內部計數有條件地寫入output。 通過在每個stage手動計算filter的一部分，可以將共享編碼到設計中。

```cpp
#include <ac_channel.h>
#include "shift_class.h"
#include "fir_filter.h"
void dec_i1(ac_channel<ac_fixed<8,1> > &x,
            ac_fixed<8,1> h[4],
            ac_channel<ac_fixed<19,4> > &y){
 static shift_class<ac_fixed<8,1>,4> regs;
 static ac_fixed<19,8> acc;
 static ac_int<1,false> cnt;

 regs << x.read();
 MAC0:for (int i = 0; i<2; i++) {
 acc += h[i+((1-cnt)<<1)]*regs[i+1-cnt];
 }
 if(cnt==1){
 y.write(acc);
 acc = 0;
 }
 cnt++;
}

```

Design constraints: 
• All IO mapped to wire enable interfaces
• All arrays mapped to registers
• Main loop pipelined with II=input rate
• MAC loop fully unrolled

第11行-每個函數調用讀取一次input data，並以II=input rate對設計進行pipeline處理，這意味著合成的硬件與上游data rate匹配。

第12到14行-由於此filter decimates by 2，因此可以將所有4 taps的計算分為兩部分。 one bit計數器“ cnt”用於將索引offset到tap shift register和coefficient array中。 static variable“temp”會累加每個階段中計算出的結果。

第15至17行-根據decimation rate有條件地write output，換句話說，將樣本丟棄。 write output後，累加器將被清除，過程重新開始。

example 158展示了如何基於input和output rate顯示共享資源。 兩種設計的decimation rate經過硬編碼，input rate為1sample/clock 或II = 1。 如果intput rate不是1 sample/clock，但是必須仍以II = 1進行流水線設計，則必須進一步改進設計以基於input output rate之比來顯示共享資源。 在single block設計中執行multi-stage decimation時，以這種方式進行編碼的原因變得顯而易見。 example 159展示了一種手動方法，對4 tap decimation filter類別進行decimate by 2，但input rate 為2。 在後面的部分中討論multi-stage decimation時，將reuse該類。

Example 159 Decimation Class for Decimate by 2, Input Rate = 2
```cpp
#ifndef _DEC2_H
#define _DEC2_H
#include <ac_fixed.h>
#include "shift_class.h"
template<int W0, int I0, int W1, int I1>
class dec2_i2{
private:
  shift_class<ac_fixed<W0,I0>,4> regs;
  ac_fixed<W0+W1,I0+I1+2> acc;
  ac_int<2,false> cnt;
  bool vld;
  bool go;
public:
  dec2_i2():vld(false), acc(0), go(false), cnt(0){}
  bool exec(ac_fixed<W0,I0> &x,
            ac_fixed<W1,I1> h[4],
            ac_fixed<W0+W1+2,I0+I1+2> &y,
            bool &vld_in,
            bool &vld_out){
    vld = false;
    if(vld_in)
    go = true;
    if(go){
    if(!(cnt&1))//read with rate 2
    regs << x;
    acc += h[cnt + 2 - (cnt[1]<<2)]*regs[cnt+(1>>cnt[1])-cnt[1]];
    if(cnt==3){//write with rate 4
    y = acc;
    acc = 0;
    vld = true;
    }
    cnt++;
    vld_out = vld;
    }
    }
};
#endif
```



```cpp
#include <ac_channel.h>
#include "shift_class.h"
#include "fir_filter.h"
#include "shift_class.h"
void fir_filter (ac_channel<ac_fixed<8,1> > &x, 
                 ac_fixed<8,1> h[4], 
                 ac_channel<ac_fixed<19,4> > &y){
    static shift_class<ac_fixed<8,1>,4> regs;
    static ac_fixed<19,8> temp;
    static ac_int<1,false> cnt;
    if(cnt==0)
        regs << x.read();
    else
        regs << 0;
    MAC0:for (int i = 0; i<2; i++) {
        temp += h[i*2+cnt]*regs[i*2+cnt];
    }
    y.write(temp);
    temp = 0;
    cnt++;
}
```
