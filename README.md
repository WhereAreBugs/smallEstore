# smallEstore
这是使用epoll的一个分支，写的很菜。
在Linux arm64上面开发的，不知道在其他架构上会不会有bug。
> 当前分支重构了整个模型  

**目前仍在开发当前项目的后端部分**

# **通信协议-键值对数据(string_to_string)** #

### Header：
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1234）|  
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |  
| Type | 4 bytes | UInt32 | 包类型 |  
| Padding | 4 bytes | UInt32 | 填充（固定为0）|  

### Types:
| Number | Meaning |  
|-|-|  
| 0 | Put请求 |  
| 1 | Delete请求 |  
| 2 | Get请求 |  
| 3 | Put响应 |  
| 4 | Delete响应 |  
| 5 | Get响应 |  

### Put Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Key Size | 4 bytes | UInt32 | Key的长度 |  
| Key | N bytes | Byte[] | Key |  
| Value Size | 4 bytes | UInt32 | Value的长度 |  
| Value | N bytes | Byte[] | Value |  

### Delete Request Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Key Size | 4 bytes | UInt32 | Key的长度 |  
| Key | N bytes | Byte[] | Key |  

### Get Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Key Size | 4 bytes | UInt32 | Key的长度 |  
| Key | N bytes | Byte[] | Key |   

### Put Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  

### Delete Response Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  

### Get Response Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Value Size | 4 bytes | UInt32 | Value的长度 |  
| Value | N bytes | Byte[] | Value |  

**默认端口**:1434  

# **通信协议-用户数据(仍在计划中)**   #

###### Header： 
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1710）|  
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |  
| Type | 4 bytes | UInt32 | 包类型 |  
| Padding | 4 bytes | UInt32 | 填充（固定为0）|  
###### Types:
| Number | Meaning |  
|-|-|  
| 0 | Register请求 |  
| 1 | Login请求 |  
| 2 | Register响应 |  
| 3 | Login响应 |  
###### Register Request Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Username Size | 4 bytes | UInt32 | Username的长度 |  
| Username | N bytes | Byte[] | Username |  
| Password Size | 4 bytes | UInt32 | Password的长度 |  
| Password | N bytes | Byte[] | Password |  
###### Login Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Username Size | 4 bytes | UInt32 | Username的长度 |  
| Username | N bytes | Byte[] | Username |  
| Password Size | 4 bytes | UInt32 | Password的长度 |  
| Password | N bytes | Byte[] | Password |  
###### Register Response Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  
###### Login Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  

#  **通信协议-图片数据(仍在计划中)**   #

###### Header：  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1712）|  
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |  
| Type | 4 bytes | UInt32 | 包类型 |  
| Padding | 4 bytes | UInt32 | 填充（固定为0）|  
###### Types:
| Number | Meaning |  
|-|-|  
| 0 | Upload请求 |  
| 1 | Download请求 |  
| 2 | Upload响应 |  
| 3 | Download响应 |  
###### Upload Request Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Image Size | 4 bytes | UInt32 | Image的长度 |  
| Image | N bytes | Byte[] | Image |  
###### Download Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Image Size | 4 bytes | UInt32 | Image的长度 |  
| Image | N bytes | Byte[] | Image |  
###### Upload Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  
###### Download Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  

#**通信协议-商品数据(仍在计划中)**  

###### Header： 
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1714）|  
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |  
| Type | 4 bytes | UInt32 | 包类型 |  
| Padding | 4 bytes | UInt32 | 填充（固定为0）|  
###### Types:  
| Number | Meaning |  
|-|-|  
| 0 | Upload请求 |  
| 1 | Download请求 |  
| 2 | Upload响应 |  
| 3 | Download响应 |  
###### Upload Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Product Size | 4 bytes | UInt32 | Product的长度 |  
| Product | N bytes | struct product | Product |  
###### Download Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Product Size | 4 bytes | UInt32 | Product的长度 |  
| Product | N bytes | struct product | Product |  
###### Upload Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  
###### Download Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  

###### struct product:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Product Name Size | 4 bytes | UInt32 | Product Name的长度 |
| Product Name | N bytes | Byte[] | Product Name |
| Product Price | 4 bytes | UInt32 | Product Price |
| Product Description Size | 4 bytes | UInt32 | Product Description的长度 |
| Product Description | N bytes | Byte[] | Product Description |
| Product Cover Image ID | 4 bytes | UInt32 | Product Image的ID,用于商品的封面 |
| Product content Image ID Size | 4 bytes | UInt64 | Product Image的ID,用于商品的详情页图片 |
| Product content Image ID | 4*N bytes | Uint64[] | Product Image的ID,用于商品的详情页图片 |
| Product category | 4 bytes | UInt32 | 商品分类 |
| Product ID | 4 bytes | UInt64 | 商品 ID |
| Product Seller ID | 4 bytes | UInt32 | Product 商家ID|
| Product level | 4 bytes | UInt32 | Product level |
 #**通信协议-订单数据(仍在计划中)**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1716）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | add order request |
| 1 | add order response |
| 2 | get order request |
| 3 | get order response |
###### add order request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| order size | 4 bytes | UInt32 | order的长度 |
| order | N bytes | struct order | order |
###### get order request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| order size | 4 bytes | UInt32 | order的长度 |
| order | N bytes | struct order | order |
###### add order response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### get order response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### struct order:
| Field | Length | Type | Meaning |
|-|-|-|-|
| order ID | 4 bytes | UInt64 | order ID |
| order buyer ID | 4 bytes | UInt32 | order buyer ID |
| order seller ID | 4 bytes | UInt32 | order seller ID |
| order product ID | 4 bytes | UInt64 | order product ID |
| order product price | 4 bytes | UInt32 | order product price |
| order product quantity | 4 bytes | UInt32 | order product quantity |
| order product total price | 4 bytes | UInt32 | order product total price |
| order product name size | 4 bytes | UInt32 | order product name size |
| order product name | N bytes | Byte[] | order product name |
| order product description size | 4 bytes | UInt32 | order product description size |
| order product description | N bytes | Byte[] | order product description |
| order product cover image ID | 4 bytes | UInt32 | order product cover image ID |
| order product content image ID size | 4 bytes | UInt64 | order product content image ID size |
| order product content image ID | 4*N bytes | Uint64[] | order product content image ID |
| order product category | 4 bytes | UInt32 | order product category |
| order product level | 4 bytes | UInt32 | order product level |
| order product seller ID | 4 bytes | UInt32 | order product seller ID |
| order product buyer ID | 4 bytes | UInt32 | order product buyer ID |
| order product buyer address size | 4 bytes | UInt32 | order product buyer address size |
| order product buyer address | N bytes | Byte[] | order product buyer address |
| order product buyer phone number size | 4 bytes | UInt32 | order product buyer phone number size |
| order product buyer phone number | N bytes | Byte[] | order product buyer phone number |
| order product buyer name size | 4 bytes | UInt32 | order product buyer name size |
| order product buyer name | N bytes | Byte[] | order product buyer name |
| order product buyer email size | 4 bytes | UInt32 | order product buyer email size |
| order product buyer email | N bytes | Byte[] | order product buyer email |
| order product buyer message size | 4 bytes | UInt32 | order product buyer message size |
| order product buyer message | N bytes | Byte[] | order product buyer message |
| order product buyer pay method | 4 bytes | UInt32 | order product buyer pay method |
| order product buyer pay status | 4 bytes | UInt32 | order product buyer pay status |
| order product buyer pay time | 4 bytes | UInt32 | order product buyer pay time |
| order product buyer pay ID size | 4 bytes | UInt32 | order product buyer pay ID size |
| order product buyer pay ID | N bytes | Byte[] | order product buyer pay ID |
| order product buyer pay amount | 4 bytes | UInt32 | order product buyer pay amount |
| order product buyer pay currency | 4 bytes | UInt32 | order product buyer pay currency |
| order product buyer pay transaction fee | 4 bytes | UInt32 | order product buyer pay transaction fee |
| order product buyer pay transaction fee currency | 4 bytes | UInt32 | order product buyer pay transaction fee currency |
| order product buyer pay transaction fee payer | 4 bytes | UInt32 | order product buyer pay transaction fee payer |
| order product status | 4 bytes | UInt32 | order product status |
| order product status time | 4 bytes | UInt32 | order product status time |
###### number of product status:
| Number | Meaning |
|-|-|
| 0 | 未付款 |
| 1 | 已付款 |
| 2 | 已发货 |
| 3 | 已收货 |
| 4 | 已评价 |
| 5 | 已取消 |
| 6 | 已退款 |
| 7 | 已退货 |
| 8 | 已退款退货 |
| 9 | 已完成 |
| 10 | 已关闭 |
| 11 | 已删除 |
| 12 | 已拒收 |
| 13 | 已退款拒收 |
| 14 | 已退货拒收 |
| 15 | 已退款退货拒收 |
| 16 | 已退款拒收退货 |
| 17 | 已退款退货拒收退货 |
| 18 | 已退款拒收退货退款 |
#**通信协议-商家数据(仍在计划中)**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1718）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | add seller request |
| 1 | add seller response |
| 2 | get seller request |
| 3 | get seller response |
###### add seller request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller size | 4 bytes | UInt32 | seller的长度 |
| seller | N bytes | struct seller | seller |
###### get seller request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller size | 4 bytes | UInt32 | seller的长度 |
| seller | N bytes | struct seller | seller |
###### add seller response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### get seller response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### struct seller:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller ID | 4 bytes | UInt32 | seller ID |
| seller name size | 4 bytes | UInt32 | seller name size |
| seller name | N bytes | Byte[] | seller name |
| seller description size | 4 bytes | UInt32 | seller description size |
| seller description | N bytes | Byte[] | seller description |
| seller cover image ID | 4 bytes | UInt32 | seller cover image ID |
| seller amount of products | 4 bytes | UInt32 | seller amount of products |
| seller amount of orders | 4 bytes | UInt32 | seller amount of orders |
| seller amount of comments | 4 bytes | UInt32 | seller amount of comments |
| seller amount of likes | 4 bytes | UInt32 | seller amount of likes |
| seller amount of views | 4 bytes | UInt32 | seller amount of views |
| seller amount of followers | 4 bytes | UInt32 | seller amount of followers |
| seller liker ID size | 4 bytes | UInt32 | seller liker ID size |
| seller liker ID | 4*N bytes | UInt32[] | seller liker ID |
| seller follower ID size | 4 bytes | UInt32 | seller follower ID size |
| seller follower ID | 4*N bytes | UInt32[] | seller follower ID |
| seller product ID size | 4 bytes | UInt32 | seller product ID size |
| seller product ID | 4*N bytes | UInt32[] | seller product ID |
| seller order ID size | 4 bytes | UInt32 | seller order ID size |
| seller order ID | 4*N bytes | UInt32[] | seller order ID |
| seller comment ID size | 4 bytes | UInt32 | seller comment ID size |
| seller comment ID | 4*N bytes | UInt32[] | seller comment ID |
| seller content image ID size | 4 bytes | UInt32 | seller content image ID size |
| seller content image ID | 4*N bytes | UInt32[] | seller content image ID |
| seller address size | 4 bytes | UInt32 | seller address size |
| seller address | N bytes | Byte[] | seller address |
| seller phone number size | 4 bytes | UInt32 | seller phone number size |
| seller phone number | N bytes | Byte[] | seller phone number |
| seller email size | 4 bytes | UInt32 | seller email size |
| seller email | N bytes | Byte[] | seller email |
| seller website size | 4 bytes | UInt32 | seller website size |
| seller website | N bytes | Byte[] | seller website |
| seller wechat size | 4 bytes | UInt32 | seller wechat size |
| seller wechat | N bytes | Byte[] | seller wechat |
#**通信协议-广场数据(仍在计划中)**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1720）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | get square post request |
| 1 | get square post response |
###### get square post request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| post ID | 4 bytes | UInt32 | post ID |
###### get square post response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| post ID | 4 bytes | UInt32 | post ID |
| post content size | 4 bytes | UInt32 | post content size |
| post content | N bytes | Byte[] | post content |
| post cover image ID size | 4 bytes | UInt32 | post cover image ID size |
| post cover image ID | 4*N bytes | UInt32[] | post cover image ID |
| post liker ID size | 4 bytes | UInt32 | post liker ID size |
| post liker ID | 4*N bytes | UInt32[] | post liker ID |
| post comment ID size | 4 bytes | UInt32 | post comment ID size |
| post comment ID | 4*N bytes | UInt32[] | post comment ID |
| post amount of likes | 4 bytes | UInt32 | post amount of likes |
| post amount of comments | 4 bytes | UInt32 | post amount of comments |
| post amount of views | 4 bytes | UInt32 | post amount of views |
| post amount of shares | 4 bytes | UInt32 | post amount of shares |
| post amount of reports | 4 bytes | UInt32 | post amount of reports |
| post amount of saves | 4 bytes | UInt32 | 收藏数量 |
#**通信协议-评论数据(仍在计划中)**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1721）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | get comment request |
| 1 | get comment response |
| 2 | add comment request |
| 3 | add comment response |
| 4 | delete comment request |
| 5 | delete comment response |
| 6 | get comment list request |
| 7 | get comment list response |
###### get comment request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| comment ID | 4 bytes | UInt32 | comment ID |
###### get comment response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| comment ID | 4 bytes | UInt32 | comment ID |
| comment content size | 4 bytes | UInt32 | comment content size |
| comment content | N bytes | Byte[] | comment content |
| comment likes | 4 bytes | UInt32 | comment likes |
| comment shares | 4 bytes | UInt32 | comment shares |
| comment replay | 4 bytes | UInt32 | comment 回复的数量 |
| comment replays | 4*N bytes | UInt32[] | comment 回复的ID |
###### add comment request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| comment content size | 4 bytes | UInt32 | comment content size |
| comment content | N bytes | Byte[] | comment content |
###### add comment response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| comment ID | 4 bytes | UInt32 | comment ID |
###### delete comment request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| comment ID | 4 bytes | UInt32 | comment ID |
###### delete comment response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### get comment list request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| comment ID size | 4 bytes | UInt32 | comment ID size |
| comment ID | 4*N bytes | UInt32[] | comment ID |
###### get comment list response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| comment ID size | 4 bytes | UInt32 | comment ID size |
| comment ID | 4*N bytes | UInt32[] | comment ID |
| comment content size | 4 bytes | UInt32 | comment content size |
| comment content | N bytes | Byte[] | comment content |
| comment likes | 4 bytes | UInt32 | comment likes |
| comment shares | 4 bytes | UInt32 | comment shares |
| comment replay | 4 bytes | UInt32 | comment 回复的数量 |
| comment replays | 4*N bytes | UInt32[] | comment 回复的ID |






*有待进一步开发*  