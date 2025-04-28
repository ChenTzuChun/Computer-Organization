# P76131432_HW1
## 開發記錄
### 1. Array Sort
- 這個部分需要實作的地方只有雙層迴圈最裡面的if判斷而已，並且有提供C code進行參照，所以實作上沒有太大的困難。
- 遇到的問題與解決方式
  1. 不太確定要怎麼取得*p_a，查詢後得知直接採用%[ ]的方式access即可
  2. 在compile的過程中有遇到問題，因為我在EXIT那行之後沒有留一行給output，導致其把:[p_a]"r"(p_a), [j]"r"(j)當作是output，因此有報錯。多新增一行: 即可正確編譯並judge。
### 2. Array Search
- 第二小題開始就沒有提供C code，所以我先把arraySearch寫成C的形式:
  ```c
  int arraySearch(int* p_a, int arr_size, int target){
    int result = 1;
    for(int i = 0; i < arr_size-1, i++){
      if(*(p_a+i) != target) i++;
      else result = i;
    }
    return result;
  }
  ```
- 這小題把C寫出來後，因為只有簡單的for loop以及if條件判斷，所以很快就寫完了，沒有遇到什麼困難。
### Linked List Sort
- 一樣先把C寫出來
  ```c
  //Block A 拆成兩個linked list
  void splitList(Node* head, Node** firstHalf, Node** secondHalf){
    Node* slow = head;
    Node* fast = head;
    while(fast != NULL && fast->next != NULL && fast->next->next != NULL){
      slow = slow->next;
      fast = fast->next->next;
    }
    *firstHalf = head;
    *secondHalf = slow->next;
    slow->next = NULL;
  }
  //Block B 合併兩個 sorted lists
  Node *mergeSortedLists(Node *a, Node *b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a; 
    Node *result; 
    if (a->data <= b->data) {
        result = a;
        a = a->next;
    } else {
        result = b;
        b = b->next;
    }
    Node *tail = result;
    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            tail->next = a;
            tail = a;
            a = a->next;
        } else {
            tail->next = b;
            tail = b;
            b = b->next;
        }
    }
    if (a != NULL)
        tail->next = a;
    if (b != NULL)
        tail->next = b;
    
    return result;
  }
  //Block C output the list
  while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
  }
  ```
- 遇到的困難與解決方式
  1. 從編譯開始就有一堆格式上的問題，大約五個，都跟一些非法操作有關，查資料後才一一修正。
  2. judge結果一直是錯誤的，不管怎麼改我的assembly code都沒辦法通過。因此我回去從C code開始進行修正: Block B 和 C 比較好確認，所以我確認過這兩部分之後應該鎖定了問題出現在Block A的部分，所以我重新把Block A 的 C 修正後如下
  ```c
  void splitList(Node *head, Node **firstHalf, Node **secondHalf) {
    *firstHalf = head;
    if (head == NULL || head->next == NULL)
        return;
    Node *slow = head;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *secondHalf = slow->next;
    slow->next = NULL;
  }
  ```
  3. 我進行了邊界條件的確認以及進行一些簡化，並依照這份code再寫一次assembly code
  4. 上述修正並未能讓結果正確，因此我上網確認關於assembly code有沒有錯誤的語法。結果是對於struct Node的組合語言理解有誤:
     - register使用可能不穩定: 我原本都是用t的暫存器，但其實這些位址都是引數，所以應該用a開頭的比較好，採用a0~a5看能不能改正。
     - offset錯誤: 因為Node的next是pointer，在64 bits環境下offset應該是8，我一直用的是4(以為只要留int的4)，所以把指標的部分從lw/sw + offset 4 改為ld/sd + offset 8。
- 經過上述的修正後最後確實輸出正確的結果。






  
