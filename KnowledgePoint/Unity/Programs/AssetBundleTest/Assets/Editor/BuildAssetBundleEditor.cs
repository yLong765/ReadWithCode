using UnityEditor;
using UnityEngine;
using UnityEngine.Windows;

public class BuildAssetBundleEditor : EditorWindow 
{
    [MenuItem("Tools/Build AssetBundle")]
    private static void Init()
    {
        GetWindow<BuildAssetBundleEditor>();
    }

    private string path = "Assets/AssetBundles";
    
    private void OnGUI()
    {
        path = EditorGUILayout.TextField(path);
        if (GUILayout.Button("build"))
        {
            BuildAssetBundle();
        }
    }

    private void BuildAssetBundle()
    {
        if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }
        BuildPipeline.BuildAssetBundles(path, BuildAssetBundleOptions.None, BuildTarget.StandaloneWindows);
        GameObject go;
        go.transform.localScale
    }
}
