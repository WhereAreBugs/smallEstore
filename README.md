# smallEstore
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
//TODO: 昵称、头像、收货地址
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
| 4 | Logout请求 |
| 5 | Logout响应 |
| 6 | GetUserInfo请求 |
| 7 | GetUserInfo响应 |
| 8 | addUserDestination请求 |
| 9 | addUserDestination响应 |
| 10 | deleteUserDestination请求 |
| 11 | deleteUserDestination响应 |
| 12 | getUserDestination请求 |
| 13 | getUserDestination响应 |
| 14 | updateUserPersonalData请求 |
| 15 | updateUserPersonalData响应 |
| 16 | resetUserPassword请求 |
| 17 | resetUserPassword响应 |



###### Register Request Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Username Size | 4 bytes | UInt32 | Username的长度 |  
| Username | N bytes | Byte[] | Username |  
| Password Size | 4 bytes | UInt32 | Password的长度 |  
| Password | N bytes | Byte[] | Password |
| isWeChat | 1 byte | Bool | 是否是微信用户 |
> 以下数据仅在isWeChat为true时才有意义，否则均应为0 

| Field | Length | Type | Meaning |  
|-|-|-|-|
| WeChatOpenID Size | 4 bytes | UInt32 | WeChatOpenID的长度 #Size为0时应不发送WeChatOpenID| 
| WeChatOpenID | N bytes | Byte[] | WeChatOpenID |
| WeChatUnionID Size | 4 bytes | UInt32 | WeChatUnionID的长度 #Size为0时应不发送WeChatUnionID| 
| WeChatUnionID | N bytes | Byte[] | WeChatUnionID |
| WeChatNickName Size | 4 bytes | UInt32 | WeChatNickName的长度 #Size为0时应不发送WeChatNickName| 
| WeChatNickName | N bytes | Byte[] | WeChatNickName |
| WeChatAvatarUrl Size | 4 bytes | UInt32 | WeChatAvatarUrl的长度 #Size为0时应不发送WeChatAvatarUrl| 
| WeChatAvatarUrl | N bytes | Byte[] | WeChatAvatarUrl |
| WeChatGender | 4 byte | UInt32 | WeChatGender #0为未知，1为男，2为女, 3为其他| 
| WeChatCountry Size | 4 bytes | UInt32 | WeChatCountry的长度 #Size为0时应不发送WeChatCountry| 
| WeChatCountry | N bytes | Byte[] | WeChatCountry | 
| WeChatProvince Size | 4 bytes | UInt32 | WeChatProvince的长度 #Size为0时应不发送WeChatProvince| 
| WeChatProvince | N bytes | Byte[] | WeChatProvince |
| WeChatCity Size | 4 bytes | UInt32 | WeChatCity的长度 #Size为0时应不发送WeChatCity| 
| WeChatCity | N bytes | Byte[] | WeChatCity |
> 以下数据仅在isWeChat为false时才有意义，否则均应为0    

| Field | Length | Type | Meaning |  
|-|-|-|-|
| userID | 4 bytes | UInt32 | 用户ID |
| Email Size | 4 bytes | UInt32 | Email的长度 #Size为0时应不发送Email| 
| Email | N bytes | Byte[] | Email |
| Phone Size | 4 bytes | UInt32 | Phone的长度 #Size为0时应不发送Phone| 
| Phone | N bytes | Byte[] | Phone |
| nickname Size | 4 bytes | UInt32 | nickname的长度  #Size为0时应不发送nickname|
| nickname | N bytes | Byte[] | nickname |
| avatar ID | 4 bytes | UInt32 | 头像的ID #Size为0时应不发送avatarUrl| 
| personal signature Size | 4 bytes | UInt32 | 个性签名的长度 #Size为0时应不发送personal signature| 
| personal signature | N bytes | Byte[] | personal signature |

###### Login Request Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Username Size | 4 bytes | UInt32 | Username的长度 |  
| Username | N bytes | Byte[] | Username |  
| Password Size | 4 bytes | UInt32 | Password的长度 |  
| Password | N bytes | Byte[] | Password |  
| userCureentLocation | 4 bytes | UInt32 | 用户当前位置 |
| amount of userAddedGroup | 4 bytes | UInt32 | 用户添加的群组数量 |
| userAddedGroup | 4*N bytes | UInt32[] | 用户添加的群组 |
| isWeChat | 1 byte | Bool | 是否是微信用户 |
###### Register Response Body:
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  
###### Login Response Body:  
| Field | Length | Type | Meaning |  
|-|-|-|-|  
| Status | 1 byte | Bool | 是否成功 |  
| isWeChat | 1 byte | Bool | 是否是微信用户 |
| ID | 4 bytes | UInt32 | 非微信用户则为用户ID，是微信用户则为WeChatOpenID |
###### Logout Request Body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| isWeChat | 1 byte | Bool | 是否是微信用户 |
| ID | 4 bytes | UInt32 | 用户ID |
###### Logout Response Body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### GetUserInfo Request Body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| isWeChat | 1 byte | Bool | 是否是微信用户 |
| ID | 4 bytes | UInt32 | 用户ID |
###### GetUserInfo Response Body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |  
| isWeChat | 1 byte | Bool | 是否是微信用户 |  
| avatar ID | 4 bytes | UInt32 | 头像的ID |  
| nickname Size | 4 bytes | UInt32 | nickname的长度 |  
| nickname | N bytes | Byte[] | nickname |  
| personal signature Size | 4 bytes | UInt32 | 个性签名的长度 |  
| personal signature | N bytes | Byte[] | personal signature |  


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

# **通信协议-商品数据(仍在计划中)**  

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
//TODO: 商品款式x3
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
| Product status | 4 bytes | UInt32 | Product status |
| Product location Size | 4 bytes | UInt32 | Product location的长度 |
| Product location | N bytes | Byte[] | Product location |
| Product time | 4 bytes | UInt32 | Product time |
| Product sales volume | 4 bytes | UInt32 | Product sales volume |

###### number of product category:
//由前端定义

 # **通信协议-订单数据(仍在计划中)**
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
| order size | 4 bytes | UInt32 | order的长度 |
| order | N bytes | struct order | order |

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
| order product transaction ID size | 4 bytes | UInt32 | order product transaction ID size |
| order product transaction ID | N bytes | Byte[] | order product transaction ID |
| order product transaction time | 4 bytes | UInt32 | order product transaction time |
| order product transaction status | 4 bytes | UInt32 | order product transaction status |

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
| 12 | 售后中 |

# **通信协议-商家数据(仍在计划中)**
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
| 4 | verify seller request |
| 5 | verify seller response |
| 6 | update seller information request |
| 7 | update seller information response |
| 8 | update seller password request |
| 9 | update seller password response |
| 10 | get seller order request |
| 11 | get seller order response |
| 12 | get seller product request |
| 13 | get seller product response |

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
###### verify seller request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller ID | 4 bytes | UInt32 | seller ID |
| seller realname size | 4 bytes | UInt32 | seller realname size |
| seller realname | N bytes | Byte[] | seller realname |
| seller ID card type | 4 bytes | UInt32 | seller ID card type |
| seller ID card size | 4 bytes | UInt32 | seller ID card size |
| seller ID card | N bytes | Byte[] | seller ID card |
| amount of seller certificate | 4 bytes | UInt32 | amount of seller certificate |
| seller certificate size | N bytes | UInt32[] | seller certificate size |
| seller certificate | N bytes | struct seller certificate | seller certificate |
###### verify seller response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
###### update seller infomation request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller size | 4 bytes | UInt32 | seller的长度 |
| seller | N bytes | struct seller | seller |
###### struct seller:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller ID | 4 bytes | UInt32 | seller ID |
| seller name size | 4 bytes | UInt32 | seller name size |
| seller name | N bytes | Byte[] | seller name |
| seller responsibility size | 4 bytes | UInt32 | seller responsibility size |
| seller responsibility | N bytes | Byte[] | seller responsibility |
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
| seller star | 4 bytes | UInt32 | seller 评级(5分制) |
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
| seller detailed address size | 4 bytes | UInt32 | seller detailed address size |
| seller detailed address | N bytes | Byte[] | seller detailed address |
| seller phone number size | 4 bytes | UInt32 | seller phone number size |
| seller phone number | N bytes | Byte[] | seller phone number |
| seller email size | 4 bytes | UInt32 | seller email size |
| seller email | N bytes | Byte[] | seller email |
| seller website size | 4 bytes | UInt32 | seller website size |
| seller website | N bytes | Byte[] | seller website |
| seller wechat size | 4 bytes | UInt32 | seller wechat size |
| seller wechat | N bytes | Byte[] | seller wechat |
| is seller verified | 1 byte | Bool | is seller verified |
| seller verified time | 8 bytes | UInt64 | seller verified time |
###### struct seller certificate:
| Field | Length | Type | Meaning |
|-|-|-|-|
| seller type | 4 bytes | UInt32 | seller type |
| seller certificate ID | 4 bytes | UInt32 | seller certificate ID |
| seller certificate image ID | 4 bytes | UInt32 | seller certificate image ID |

###### struct seller type:
//由前端定义

# **通信协议-广场数据(仍在计划中)**
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
| 2 | get user square groups request |
| 3 | get user square groups response |
| 4 | get square group request |
| 5 | get square group response |
| 6 | get square group posts request |
| 7 | get square group posts response |
| 8 | get square post comments page request |
| 9 | get square post comments page response |
###### get square post request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| post ID | 4 bytes | UInt32 | post ID |
###### get square post response body:
//分类列表：农生活、好物分享、滞销帮
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
| post comment ID pages | 4 bytes | UInt32 | 评论的页数 |
| post comment ID size | 4 bytes | UInt32 | 评论的数量、单页q最大返回20 |
| post comment ID | 4*N bytes | UInt32[] | 评论的标识ID |
| post amount of likes | 4 bytes | UInt32 | 点赞数量 |
| post amount of comments | 4 bytes | UInt32 | 评论数量 |
| post amount of views | 4 bytes | UInt32 | 帖子的浏览数 |
| post release time | 8 bytes | UInt64 | 发布的时间戳 |
| post amount of saves | 4 bytes | UInt32 | 收藏数量 |

# **通信协议-评论数据**
//TODO: 标签(关键字、回头客)、评论时间、内容可以发送图片和视频
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


# **通信协议-普通搜索(仍在计划中)**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1722）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | product search request |
| 1 | product search response |
| 2 | user search request |
| 3 | user search response |
| 4 | square post search request |
| 5 | square post search response |


###### search request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| search content size | 4 bytes | UInt32 | search content size |
| search content | N bytes | Byte[] | search content |
###### search response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| search result size | 4 bytes | UInt32 | search result size |
| search result | N bytes | Byte[] | search result |
| search result type | 1 byte | Byte | search result type |
| search result ID | 4 bytes | UInt32 | search result ID |


# **通信协议-商品预约**  
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1723）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | get product reservation request |
| 1 | get product reservation response |
| 2 | add product reservation request |
| 3 | add product reservation response |
| 4 | delete product reservation request |
| 5 | delete product reservation response |
| 6 | get product reservation list request |
| 7 | get product reservation list response |
###### get product reservation request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| product ID | 4 bytes | UInt32 | product ID |
###### get product reservation response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| product ID | 4 bytes | UInt32 | product ID |
| product reservation size | 4 bytes | UInt32 | product reservation size |
| product reservation | N bytes | Byte[] | product reservation |
###### add product reservation request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| product ID | 4 bytes | UInt32 | product ID |
| product reservation size | 4 bytes | UInt32 | product reservation size |
| product reservation | N bytes | Byte[] | product reservation |
###### add product reservation response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| product ID | 4 bytes | UInt32 | product ID |
| product reservation size | 4 bytes | UInt32 | product reservation size |
| product reservation | N bytes | Byte[] | product reservation |
###### delete product reservation request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| product ID | 4 bytes | UInt32 | product ID |
    
###### delete product reservation response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| product ID | 4 bytes | UInt32 | product ID |
###### get product reservation list request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| product ID size | 4 bytes | UInt32 | product ID size |
| product ID | 4*N bytes | UInt32[] | product ID |
###### get product reservation list response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| product ID size | 4 bytes | UInt32 | product ID size |
| product ID | 4*N bytes | UInt32[] | product ID |
| product reservation size | 4 bytes | UInt32 | product reservation size |
| product reservation | N bytes | Byte[] | product reservation |




# **通信协议-旅游信息(景点、商业[民宿、农家乐、商铺推荐])**  

//TODO: 文字、语音、图片、群成员
# **通信协议-广场群聊**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|

# **通信协议-消息列表**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1724）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | get message list request |
| 1 | get message list response |
| 2 | get message request |
| 3 | get message response |
| 4 | send message request |
| 5 | send message response |
| 6 | delete message request |
| 7 | delete message response |
###### get message list request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| message ID size | 4 bytes | UInt32 | message ID size |
| message ID | 4*N bytes | UInt32[] | message ID |
//TODO: 物流、优惠、交易通知、官方消息、客服消息
###### get message list response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| message ID size | 4 bytes | UInt32 | message ID size |
| message ID | 4*N bytes | UInt32[] | message ID |

# **通信协议-商家客服系统**  
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1723）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | send message |
| 1 | receive message |
| 2 | send image |
| 3 | receive image |
| 4 | send voice |
| 5 | receive voice |
| 6 | send video |
| 7 | receive video |

###### send message body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| message content size | 4 bytes | UInt32 | message content size |
| message content | N bytes | Byte[] | message content |
###### receive message body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| message content size | 4 bytes | UInt32 | message content size |
| message content | N bytes | Byte[] | message content |
###### send image body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| image size | 4 bytes | UInt32 | image size |
| image | N bytes | Byte[] | image |
###### receive image body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| image size | 4 bytes | UInt32 | image size |
| image | N bytes | Byte[] | image |
###### send voice body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| voice size | 4 bytes | UInt32 | voice size |
| voice | N bytes | Byte[] | voice |
###### receive voice body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| voice size | 4 bytes | UInt32 | voice size |
| voice | N bytes | Byte[] | voice |
###### send video body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| video size | 4 bytes | UInt32 | video size |
| video | N bytes | Byte[] | video |
###### receive video body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| video size | 4 bytes | UInt32 | video size |
| video | N bytes | Byte[] | video |

# **通信协议-官方客服系统**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1000）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|
###### Types:
| Number | Meaning |
|-|-|
| 0 | send message |
| 1 | receive message |
| 2 | send image |
| 3 | receive image |
| 4 | send voice |
| 5 | receive voice |
| 6 | send video |
| 7 | receive video |

###### send message body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| message content size | 4 bytes | UInt32 | message content size |
| message content | N bytes | Byte[] | message content |
###### receive message body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| message content size | 4 bytes | UInt32 | message content size |
| message content | N bytes | Byte[] | message content |
###### send image body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| image size | 4 bytes | UInt32 | image size |
| image | N bytes | Byte[] | image |
###### receive image body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| image size | 4 bytes | UInt32 | image size |
| image | N bytes | Byte[] | image |
###### send voice body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| voice size | 4 bytes | UInt32 | voice size |
| voice | N bytes | Byte[] | voice |
###### receive voice body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| voice size | 4 bytes | UInt32 | voice size |
| voice | N bytes | Byte[] | voice |
###### send video body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| video size | 4 bytes | UInt32 | video size |
| video | N bytes | Byte[] | video |
###### receive video body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| video size | 4 bytes | UInt32 | video size |
| video | N bytes | Byte[] | video |

# **通信协议-购物车**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1725）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| user ID | 4 bytes | UInt32 | 用户ID |
###### Types:
| Number | Meaning |
|-|-|
| 0 | get cart list request |
| 1 | get cart list response |
| 2 | add cart request |
| 3 | add cart response |
| 4 | delete cart request |
| 5 | delete cart response |
| 6 | update cart request |
| 7 | update cart response |
###### get cart list request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| cart ID size | 4 bytes | UInt32 | cart ID size |
| cart ID | 4*N bytes | UInt32[] | cart ID |
//TODO: 降价、缺货、促销、新品
###### get cart list response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| cart ID size | 4 bytes | UInt32 | cart ID size |
| cart ID | 4*N bytes | UInt32[] | cart ID |

# **通信协议-足迹**
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为1725）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| user ID | 4 bytes | UInt32 | User ID |
###### Types:
| Number | Meaning |
|-|-|
| 0 | get footprint list request |
| 1 | get footprint list response |
| 2 | add footprint request |
| 3 | add footprint response |
| 4 | delete footprint request |
| 5 | delete footprint response |
###### get footprint list request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| footprint ID page | 4 bytes | UInt32 | footprint ID page |
| footprint ID | 4*N bytes | UInt32[] | footprint ID |
###### get footprint list response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| footprint ID page | 4 bytes | UInt32 | footprint ID total page |
| footprint ID size | 4 bytes | UInt32 | footprint ID size |
| footprint ID | 4*N bytes | UInt32[] | footprint ID |
###### add footprint request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| type | 1 byte | UInt8 | 历史记录的类型(商品、旅游、商家等) | 
| ID | 4 bytes | UInt32 | 历史记录类型对应的ID |
| time | 8 bytes | UInt64 | 历史记录的时间(后端仅作存储和排序，前端可自由定义。推荐使用union来记录或者时间戳) |

###### add footprint response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |

###### delete footprint request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| type | 1 byte | UInt8 | 历史记录的类型(商品、旅游、商家等) |
| footprint ID | 4 bytes | UInt32 | footprint ID |

###### delete footprint response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |

###### get footprint request body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| type | 1 byte | UInt8 | 历史记录的类型(商品、旅游、商家等) |
| footprint ID | 4 bytes | UInt32 | footprint ID |

###### get footprint response body:
| Field | Length | Type | Meaning |
|-|-|-|-|
| Status | 1 byte | Bool | 是否成功 |
| 

# **通信协议-优惠券**
//TODO: 店铺优惠券、商品优惠券、满减

# **通信协议-发现**

# **通信协议-我的**

# **通信协议-支付**

# **通信协议-反馈**

# **通信协议-成长**
//TODO: 学农识、听讲座、学经营、看新闻

# **通信协议-收藏**

# **通信协议-问诊**
//TODO: 分类、在线问诊、预约问诊、问诊记录

# **通信协议-行情**
//TODO: 消费者预约结果、分月份、天数汇总结果数据、筛选品种、地区、价格

# **通信协议-借贷**

# **通信协议-活动**
//TODO: 节日活动、入驻活动
###### Header：
| Field | Length | Type | Meaning |
|-|-|-|-|
| MagicNumber | 4 bytes | UInt32 | 魔数（固定为7456）|
| Size | 4 bytes | UInt32 | 包大小，不包括头部 |
| Type | 4 bytes | UInt32 | 包类型 |
| Padding | 4 bytes | UInt32 | 填充（固定为0）|

# **通信协议-推广**

# **通信协议-经营分析**
//TODO: 日销售额、月销售额、总销售额、交易明细

# **通信协议-排行榜**