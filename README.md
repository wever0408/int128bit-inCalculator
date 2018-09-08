# int128bit-inCalculator
﻿Quy định cấu trúc tập tin Input:   
- Gồm n dòng: không biết trước giá trị n 
- Trong mỗi dòng, sẽ có chỉ thị p có các giá trị sau đây (các chỉ thị này được phân biệt với các 
toán hạng phía sau bằng đúng 1 ký tự khoảng trắng): 
o p = 2: thực hiện tính toán, xử lý ở chế độ Binary  
o p = 10: thực hiện tính toán, xử lý ở chế độ Decimal 
o p = 16: thực hiện tính toán, xử lý ở chế độ Hexa  
 
- Nếu trong 1 dòng có 2 chỉ thị p1 và p2 (p1 và p2 cách nhau bởi đúng 1 khoảng trắng): có 
nghĩa là chuyển toán hạng ở chế độ p1 sang chế độ p2. 
- Trong một dòng, các toán tử hai ngôi và toán hạng được cách nhau bởi đúng 1 khoảng trắng. 
- Độ dài dãy bit nhị phân, dãy hexa không cố định và không vượt quá 128 bit.  
- Mặc định dữ liệu trên từng dòng đã có tính đúng đắn, không cần xét tính hợp lệ của dữ liệu
đầu vào. Mỗi thành phần trên một dòng cách nhau bởi đúng 1 khoảng trắng.  
