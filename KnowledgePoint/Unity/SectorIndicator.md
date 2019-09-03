# 扇形技能指示器

网上基本有两种方法写扇形指示器：

1. 生成Mesh拼接
2. Shader绘制

## Mesh拼接

我这边用Unity自带的Gizmos简单的绘制一下Mesh

注意：Gizmos.DrawMesh()中的Mesh必须包含vertices和normals

### 生成vertices

```csharp
/// <summary>
/// 生成vertices
/// </summary>
/// <param name="precision">三角形数量</param>
/// <param name="originPos">原点</param>
/// <param name="forward">朝向</param>
/// <returns>vertuces</returns>
private Vector3[] GetVectors(int precision, Vector3 originPos, Vector3 forward)
{
    // 一共需要三角形数量+2的顶点数
    Vector3[] meshVectors = new Vector3[precision + 2];
    // 每个三角形的角度
    float meshRadius = angle / precision;
    // 起始三角形朝向
    forward = Quaternion.AngleAxis(-angle / 2, Vector3.up) * forward;
    // 特殊设置0与1的顶点位置
    meshVectors[0] = originPos;
    meshVectors[1] = originPos + forward * radius;
    // 后续定点按规律生成
    for (int i = 2; i < precision + 2; i++)
    {
        // 旋转一个三角形的朝向
        forward = Quaternion.AngleAxis(meshRadius, Vector3.up) * forward;
        // 设置定点
        meshVectors[i] = originPos + forward * radius;
    }
    return meshVectors;
}
```

### 生成Triangles

```csharp
/// <summary>
/// 生成triangles
/// </summary>
/// <param name="precision">三角形数量</param>
/// <returns>triangles</returns>
private int[] GetTriangles(int precision)
{
    // 每个三角形三个triangle
    int[] meshTriangles = new int[precision * 3];
    // 按规律生成
    for (int i = 0; i < precision; i++)
    {
        int id = i * 3;
        meshTriangles[id] = 0;
        meshTriangles[id + 1] = i + 1;
        meshTriangles[id + 2] = i + 2;
    }
    return meshTriangles;
}
```

### 利用OnDrawGizmos绘制三角形

```csharp
public float angle; // 角度
public float radius; // 半径
public int precision; // 三角形数量（越多约成圆，效率越低）
public GameObject origin; // 原点GameObject（表示原点位置用）
private void OnDrawGizmos()
{
    Mesh mesh = new Mesh();
    mesh.vertices = GetVectors(precision, origin.transform.position, origin.transform.forward);
    mesh.triangles = GetTriangles(precision);
    // 生成normals
    mesh.RecalculateNormals();
    Gizmos.color = Color.red;
    // 画线框（Mesh会挡住线框的绘制）
    for (int i = 1; i < mesh.vertices.Length; i++)
    {
        Gizmos.DrawLine(mesh.vertices[0], mesh.vertices[i]);
        Gizmos.DrawLine(mesh.vertices[i], mesh.vertices[i - 1]);
    }
    // 画Mesh
    Gizmos.DrawMesh(mesh);
}
```

## Shader绘制

### 属性

```c++
_Inner ("Inner Texture", 2D) = "white" {} // 内圈贴图
_Outer ("Outer Texture", 2D) = "white" {} // 外圈贴图
_Color ("Color", Color) = (1, 1, 1, 1)    // 颜色
_Angle ("Angle", Range(0, 360)) = 60	  // 角度
_OutLine ("Out Line", Range(0, 1)) = 0.1  // 外圈宽度
```

### 核心剔除代码

```c++
fixed4 frag(fragmentInput i) : SV_Target 
{
	// 距离超过半径则剔除
    float distance = pow(i.uv.x - 0.5, 2) + pow(i.uv.y - 0.5, 2);
    if (distance > 0.25f) {
        discard;
    }

    float x = i.uv.x;
    float y = i.uv.y;
    float deg2rad = 0.017453; // 角度转弧度

    if (_Angle > 180) {
        if(y > 0.5 && abs(0.5 - y) >= abs(0.5 - x) / tan((180 - _Angle / 2) * deg2rad)) {
        	discard;
        }
        else {
        if(y > 0.5 || abs(0.5 -y) < abs(0.5 - x) / tan(_Angle / 2 * deg2rad)) {
        	discard;
        }
    }
	// 外圈显示比例
    float outDis = 0.25 * pow((1 - _OutLine), 2);

    if (distance > outDis) {
    	// 外圈绘制
    	return tex2D(_Outer, i.uv) * _Color;
    }
    else {
    	// 内圈绘制
    	return tex2D(_Inner, i.uv) * _Color;
    }
}
```



```c++
Shader "Unlit/SectorShader" 
{
    Properties {
        _Inner ("Inner Texture", 2D) = "white" {}
        _Outer ("Outer Texture", 2D) = "white" {}
        _Color ("Color", Color) = (1, 1, 1, 1)
        _Angle ("Angle", Range(0, 360)) = 60
        _OutLine ("Out Line", Range(0, 1)) = 0.1
    }

    SubShader {
        Tags { "Queue"="Transparent" "RenderType"="Transparent" "IgnoreProjector"="True" }
        Pass {
            ZWrite Off
            Blend SrcAlpha OneMinusSrcAlpha
            CGPROGRAM
 
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"

            sampler2D _Inner;
            sampler2D _Outer;
            float4 _Color;
            float _Angle;
            float _OutLine;
 
            struct fragmentInput 
            {
                float4 pos : SV_POSITION;
                float2 uv : TEXCOORD0;
            };

            fragmentInput vert (appdata_base v)
            {
                fragmentInput o;

                o.pos = UnityObjectToClipPos (v.vertex);
                o.uv = v.texcoord.xy;

                return o;
            }
 
            fixed4 frag(fragmentInput i) : SV_Target 
            {
                float distance = pow(i.uv.x - 0.5, 2) + pow(i.uv.y - 0.5, 2);
                if (distance > 0.25f)
                {
                    discard;
                }
                
                float x = i.uv.x;
                float y = i.uv.y;
                float deg2rad = 0.017453; // 角度转弧度

                if (_Angle > 180)
                {
                    if(y > 0.5 && abs(0.5 - y) >= abs(0.5 - x) / tan((180 - _Angle / 2) * deg2rad))
                    {
                        discard;
                    }
                }
                else
                {
                    if(y > 0.5 || abs(0.5 -y) < abs(0.5 - x) / tan(_Angle / 2 * deg2rad))
                    {
                        discard;
                    }
                }
                
                float outDis = 0.25 * pow((1 - _OutLine), 2);
                
                if (distance > outDis)
                {
                    return tex2D(_Outer, i.uv) * _Color;
                }
                else
                {
                    return tex2D(_Inner, i.uv) * _Color;
                }
            }
            
            ENDCG
        }
    }  
    FallBack "Diffuse"
}
```

