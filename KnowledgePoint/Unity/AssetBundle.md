# AssetBundle

------

## AssetBundle的分包策略

### 逻辑实体分组

指资源根据项目的功能部分进行分包，如用户界面，字符等，如：

* 用户UI所有的纹理和布局数据
* 字符/字符集所有的模型和动画

逻辑实体分组是可下载内容（DLC）的理想选择，开发人员必须准确熟悉项目使用的每个资源的时间和地点

### 类型分组

将例如声音或者本地化文件分配给单独的AssetBundle

类型分组是构建AssetBundle以供多个平台使用的更好的策略之一

### 并发内容分组

适用于关卡类型的游戏，在同一时间只会用到其中一个AssetBundle

### 分组注意事项：

* 强频繁更新的对象拆分为AssetBundle，与很少更新的对象分开
* 对可能同时加载的对象进行分组
* 如果多个AssetBundle中的多个对象以来与来自完全不同的AssetBundle的单个资产，则将以来项移动到单独的AssetBundle中
* 如果多个AssetBundle引用其他AssetBundle中的同一组资产，则将这些依赖放入共享AssetBundle以减少重复
* 如果一个AssetBundle中的两组对象不可能同时加载（比如低模和高模），则将其分成两个AssetBundle
* 考虑合并小型（少于5到10个Asset）但其内容经常同时加载的AssetBundle
* 如果同时经常加载一个AssetBundle其中50%的资源，考虑分AssetBundle
* 一组对象只是同一对象的不同版本，考虑AssetBundle Variants

------

## 构建AssetBundle

*  BuildAssetBundleOptions：Unity提供了三种特定的压缩方式：
   *  BuildAssetBundleOptions.None：使用LZMA格式压缩，压缩成序列化数据文件流。解压缩后会使用LZ4压缩格式重新再本地磁盘上压缩
      *  优点：文件小
      *  缺点：解压缩，加载时间略长。如要使用包中的任何资源，必须先解压缩整个包
   *  BuildAssetBundleOptions.UncompressedAssetBundle：不压缩
      *  优点：加载速度快
      *  缺点：包体大
   *  BuildAssetBundleOptions.ChunkBasedCompression：使用LZ4格式压缩
      *  优点：比LZMA大，比不压缩小，不需要使用资源解压整个包，加载速度相当于未压缩。
*  BuildTarget：表明AssetBundle使用的目标平台

```csharp
using UnityEditor;
using System.IO;

public class CreateAssetBundles
{
    [MenuItem("Assets/Build AssetBundles")]
    static void BuildAllAssetBundles()
    {
        string assetBundleDirectory = "Assets/AssetBundles";
        if(!Directory.Exists(assetBundleDirectory))
        {
            Directory.CreateDirectory(assetBundleDirectory);
        }
		BuildPipeline.BuildAssetBundles(assetBundleDirectory, BuildAssetBundleOptions.None, BuildTarget.StandaloneWindows);
    }
}
```

### 构建文件解析

#### AssetBundle文件

非.manifest扩展名的文件，包含运行时加载以及资源的内容，包体结构分为两种，普通AssetBundle和Scene AssetBundle

* 普通AssetBundle结构：

![AssetBundle Container](D:\Work\GitProgram\ReadWithCode\KnowledgePoint\Unity\Img\AssetBundle\AssetBundle Container.png)

* Scene AssetBundle：针对Scene的流加载优化

#### 清单文件

对于生成的每个包（包括附加的Manifest Bundle），都会生成关联的清单文件。包含循环亢余校验（CRC）数据和包体的依赖数据等信息

普通AssetBundle清单信息

```json
ManifestFileVersion: 0
CRC: 3507989386 // 循环亢余校验
Hashes:
  AssetFileHash:
    serializedVersion: 2
    Hash: 8389c134be6df93381072ffcc166568f
  TypeTreeHash:
    serializedVersion: 2
    Hash: c0f34e0e405254bd5ec86cc7a8aa1b79
HashAppended: 0
ClassTypes:
- Class: 1
  Script: {instanceID: 0}
- Class: 4
  Script: {instanceID: 0}
- Class: 21
  Script: {instanceID: 0}
- Class: 23
  Script: {instanceID: 0}
- Class: 48
  Script: {instanceID: 0}
- Class: 84
  Script: {instanceID: 0}
- Class: 114
  Script: {fileID: 11500000, guid: 0d2d6d01e1a89684e87fe223c792fc41, type: 3}
- Class: 115
  Script: {instanceID: 0}
Assets: // 资源地址
- Assets/Art/NewSurfaceShader.shader
- Assets/Art/GameObject.prefab
- Assets/Art/New Render Texture.renderTexture
- Assets/Art/New Material.mat
Dependencies: []
```

生成的Manifest Bundle清单信息

```json
ManifestFileVersion: 0
CRC: 4271312968 // 循环亢余校验
AssetBundleManifest:
  AssetBundleInfos:
    Info_0:
      Name: asset1.a
      Dependencies: {}
```









