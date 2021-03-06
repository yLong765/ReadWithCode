# 《Unity实战》重点记录

## 零散知识点

* Transform.localEulerAngles
  * 相对于父物体的旋转角（欧拉角）
  * 次角度不能超过360度，如果要增量，改用Transform.Rotate
  * Unity将会将角度自动转换为Transform.localRotation的四元数角度中
* Transform.TransformDirection(Vector3)
  * 将向量方向从本地空间转换为世界空间
  * 长度不变
  * 方向为主
* Transform.TransformPoint(Vector3)
  * 将位置从本地空间转换为世界空间
  * 位置为主
  * Transform.InverseTransformPoint : 从世界转为本地
* 2D图像导入设置Pixels-To-Units：因Unity最开始是3D引擎，2D后来才加入，所以Unity中的一个单位不一定是图像中的一个像素。Pixels-To-Units设置为1:1则为Unity的一图像对应一像素，建议使用默认的100:1(因物理引擎在1:1的状态下不能正常工作)
* 销毁GameObject：为了显示场景中的对象，Unity需要在场景图中引用所有对象。因此即使移除代码中所有对GameObject的引用，它依然会被这个场景引用，以防止对象被自动销毁。因此，Unity提供了Destroy方法来告诉游戏引擎“将这个对象从场景中移除”。Unity重载了==操作符，当检查null的时候返回true。技术上，对象依然存在于内存中，但它可能不再存在，因此Unity让它显示为null。调用已销毁物体的GetInstanceID方法，就可以确认。
* int num = Random.Range(num1, num2)：num1 <= num < num2 取值范围
* SendMessage注意：C#这种强类型语言中使用面向对象编程时，需要知道目标类型才能和该对象通信，SendMessage的效率比调用已知类型的公有方法低
* 直接调整position的值，碰撞检测无法工作
* Sprite Renderer.Order in Layer：同Z轴情况下控制前后层级，值越大，就在上层
* 贴图的Texture Type设置在3D中默认为Texture，2D中默认为Sprite
* LateUpdate：所有对象的Update都运行完之后才执行LateUpdate方法
* 位置向量乘以四元数，结果是基于旋转的便宜位置。
* Lerp(linear interpolation)线性插值：有专为四元数提供的插值Slerp(spherical linear interpolation)球形线性插值，对于更慢的变换，Slerp比Lerp表现的更好

## 美术资源的类型

美术资源的类型 | 该类型的定义
- | -
2D图像 | 扁平的图片
3D模型 | 3D虚拟对象（网络对象）
材质 | 定义了附加材质的对象的表面属性。包括颜色、发光等
动画 | 打包了关联对象的运动信息。描述运动序列，而不是及时计算位置的代码
粒子系统 | 用于创建并控制大量小型对象的规则机制。例如烟雾、火焰等

## 白盒

用粗糙的版本快速的搭建一个可以运行的场景，并且测试是否符合设计要求，然后再填补细节

## 贴图

用于提高3D图形效果的2D图像，最直接的作用就是显示在3D模型的表面上。

贴图大小应为2的幂。4、8、16、32、64、128、256、512、1024、2048（再大就不适合贴图了）

### 2D图像文件格式

文件类型 | 优缺点
- | -
PNG | 无损压缩，带透明通道（优先选用）
JPG | 有损压缩，无通明通道
GIF | 有损压缩，无透明通道（消耗并不是压缩造成的，而是图片转为八位时导致数据丢失。最终导致了消耗）
BMP | Windows上默认的图像格式。无压缩，无透明通道
TGA | 常用于3D图形。无损压缩活不压缩，带透明通道
TIFF | 常用于数字相片和出版。无损压缩或不压缩，无透明通道
PICT | 就Macs系统上默认的图像格式。有损压缩，无透明通道
PSD | Photoshop原生文件格式。无压缩，有透明通道。

通明通道用于保存图像的透明信息。可见颜色来自三个通道的信息：红、绿、蓝。Alpha是附加的通道信息。

平铺图像（无缝平铺图像）：排列在一起时对边能互相匹配的图像。能重复平铺，没有可见缝隙。

## 材质

贴图可以是材质的一部分，材质可以应用到几何体上。材质是定义表面属性的一系列信息。这种间接方式导致了同一个贴图可以用于多个材质。

## 天空盒

是一个包围射线机的立方体，这个立方体每个面都用天空图片贴图。

## 着色器

一种简短的程序，它列出了绘制表面内容的指令，包括是否使用贴图。计算机在渲染图像时使用这些指令来计算像素。

## 3D模型

### 3D模型文件格式

文件类型 | 优缺点
- | -
FBX | 网格和动画（推荐）
Collada(DAE) | 网格和动画
OBJ | 网格；文本格式，有时用于互联网上传输流
3DS | 网格；（过时）
DXF | 网格；（过时）
Maya | 支持FBX导出
3ds Max | 支持FBX导出
Blender | 支持FBX导出

## 2D图像

### 零散知识点

* 在Unity中2D的Z坐标影响对象的堆叠。Z值越低，离摄像机越近
* Pixels-To-Units为100意味着100像素就是Unity中的1单位
* Projection = Orthographic的情况下Size表示屏幕中心到屏幕顶点的大小
* 像素完美(Pixel-perfect)：意味着屏幕上的一个像素对应图像中的一个像素（否则，视频卡会让图像在缩放到填满屏幕时变得模糊)。假设要在1024*768中实现像素完美：则距离为SCREEN_SIZE / 2 / Pixels-To-Units：768 / 2 / 100 = 3.84

### 图集

* 概念：将多个图片组合成一张图片叫做图集（精灵表）
* 应用：2D帧动画通常用图集表示
* 优点：
    1. 减少空间的浪费（紧凑打包）
    2. 减少DrawCall

### 文本

* 在场景中创建3D文本对象：TextMesh(TextMesh Pro更好)
  * 用Arial自体，增加FontSize为文本显示提供很多像素，利用缩放来把像素亚索到很小的空间（优化的有点迷，牺牲清晰度的优化）

### 动画

* 核心：
  * 动画剪辑：单个循环动画
  * 动画控制器：合适播放动画的控制器
    * Hsh Exit Time：允许在动画播放时切换

### GUI

* HUD（平视显示）：使图形叠加在世界视图上
* 立即模式：（OnGUI），在没帧显式发出绘制命令
  * 可以在放置UI元素时看到当前UI的外观
  * 容易使用自己的图像来定制UI
* 保留模式：一次定义所有的视觉效果，之后系统就知道每帧绘制什么，不必再重新生命。

### Canvas

* 1单位 == 1像素
* Render Mode
  * Screen Space - Overlay：将UI渲染为摄像机视图顶部的2D图像
  * Screen Space - Camera：将UI渲染在摄像机视图顶部，但UI元素可以旋转，可以有透视效果（UI中的粒子特效需要用这种方式）
  * World Space：将画布放在场景中，UI是场景的一部分
* Pixel Perfect：轻微调整图像位置，使图像更加清晰

所有UI都有锚点（anchor）：是对象附加到画布或屏幕的点。它决定了计算对象的位置所依赖的点。

* InputField
  * OnEndEdit
    * Static Paraneters：发送提前定义好的字符串
    * Dynamic String：发送输入域中输入的内容