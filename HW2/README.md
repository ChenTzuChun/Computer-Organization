# P76131432_HW2
## 開發記錄
### 1. Fast Fourier Transform Calculation
- 第一題要寫六個c檔來完成FFT，分別是針對複數做加減乘運算的complex_add, complex_sub, complex_mul檔，定義pi的pi檔，算位數的log2檔以及將整串bit反轉的bit_reverse檔。
- 思考流程依樣都是先從函式的C code出發，有些函式也有提供簡單的C code。前三個運算函式相對簡單，沒有遇到什麼困難。
- 後面三個檔的 C code 如下
```c
#pi
float pi = 0.0;
for(int i = 0; i < N; i++){
  float term = 1.0/(2 * i + 1);
  if(i % 2 == 1){
    pi = pi + term;
  }
  else pi = pi - term;
}

#log2
while (N > 1) {
  N = N >> 1;  
  log++;
}

#bit_reverse
int reversed = 0;
for (int i = 0; i < m; i++) {
    reversed = (reversed << 1) | (b & 1);
    b = b >> 1; 
}
```
- 上面只有列出我需要寫的部分，以及最後參考的版本。
- 遇到的問題與解決方式
  1. 寫assembly code時遇到比較大的問題是在寫bit_reverse的時候，我寫了三個版本的C code。前兩個版本發現暫存器個數一定會超出限制才能寫出來，最終的版本如上述所列。考慮暫存器個數的限制算是寫組合語言時除了邏輯以外花最多時間處理的事情。
  2. 寫完全部的組合語言後直接去測試，最後的FFT結果跟Reference answer一直沒辦法對上，花了非常長一段時間在debug。把後面三個比較容易出錯的檔案用print法找錯，最後確定後面三個應該沒錯後才去細讀FFT內部的運作，實在找不到問題點後才與同學討論。發現有人有相同的問題，問題出在做複數乘法的那個檔案裡，C_Re跟B_Re兩個存的變數用到同一個暫存器，有early clobber問題。後來因為不確定能不能動exercise1檔案，就把complex_mul的檔案裡對C_Re,B_Re的操作指令隔開一點才使輸出結果符合預期。
  3. others_cnt對不上的問題。最後針對後三個有寫到branch檔做排查才發現有一條指令多計算了。
### 2-1 Array Multiplication without V Extension
- 第二題之後都有提供C code，就不用自己寫了
- 這部分就是簡單的流程控制跟計算，沒有什麼問題。
### 2-2 Array Multiplication with V Extension
- 這部分的困難就是理解V extension花了一段時間，但理解了之後也沒有什麼寫組合語言上的困難。
### 3-1 Single Floating-point Multiplication
- 這部分邏輯也不困難，所以也沒有花很多時間
### 3-2 Double Floating-point Multiplication
- 這部分稍微理解了一下單精度跟被精度在操作上的差異，其餘跟3-1一模一樣。
### macro_define.h
- 用來計算instruction count, ratio, execution time的巨集，計算內容不太會出錯，也沒有遇到很難處理的錯誤。

- 最後每一題在本地的測試都有通過，除了第一題以外沒有遇到太大的困難，希望隱藏測茲也能順利通過。
