# P76131432_HW3
## 開發記錄
### 1. Implement FIFO Data Cache Replacement Policy
- 第一題是要實作 FIFO strategy 來選擇 victim way，要分別對一般的cache以及fully associative cache做修正。


  原本這兩種cache皆使用random select，只需要改成FIFO就可以了。實作FIFO最簡單的方式就是使用queue，所以我直接使用include queue來使用
- head檔只是新增了queue的宣告，對於一般的cache需要宣告vector，因為會有index欄位，我必須要知道現在在對哪個index的way做操作。
而 fully associative cache 只有一個 set，所以不需要 index，每個 way 都屬於同一個的 queue。
- cc檔的部分就是利用在head宣告的queue vector及 queue來寫FIFO的運作邏輯。對於一般的cache就是判斷在某個index的queue大小是不是超過能容許的way總數，如果是的話就把queue中最前面的way pop掉再push現在這個進去。
而 fully-associative cache，FIFO 是直接對 tag 做操作，因為 tag 就是唯一能分辨不同 cache line 的依據。

- 遇到的困難：
> 這部分最大的困難不是在寫FIFO，是架設環境以及測試的部分。
>
> 
> - 環境架設要花蠻長一段時間，失敗一次的時間成本很高，處理了約3小時才完成
>
> 
> - 測試的部分光是要理解在哪裡測試以及要怎麼測試就花了一段時間，最後自己寫了一小段測試，成功通過後才放心往下寫。
### 2. Enhancing Software Programs to Reduce Memory Access Overhead
- 第二題是要根據硬體上讀取的特性來分別修改矩陣轉置以及矩陣乘法的 code ，並達到一定的效能。
- 2-1的部分是修改矩陣轉置，原本只能想到修改行列讀取的順序減少他的 miss rate，後來發現好像不太夠，就上網搜尋有沒有其他辦法。
最後找到可以把它切成好幾個 blocks，將整個矩陣劃分為多個 blocks後，能在處理每個 block 時提高快取命中率，可以有效降低整體 cache miss。
- 2-2的部分是修改矩陣乘法，其實就是改成 a 跟 b 的轉置相乘，然後轉置的方式就採用2-1的優化方法，最後也是成功達到目標效能。這邊我使用了 malloc 來動態分配空間，怕隱藏測資的資料太大。
- 遇到的困難：
> 這題最大的困難是想分block這個方法，一開始沒有什麼除了行列讀取以外能優化的想法所以上網看了一些優化方式，最後才順利處理。其他沒有特別大的困難。
