using System.IO;
using UnityEngine;

public class LoadAsset
{
    public static void LoadAssetAndInstantiate()
    {
        var assetbundle = AssetBundle.LoadFromFile(Path.Combine("Assets/AssetBundles", "asset.a"));
        var gameObject = assetbundle.LoadAsset<GameObject>("prefab1");
        Object.Instantiate(gameObject);
    }

    public static void LoadManifest()
    {
        var assetbundle = AssetBundle.LoadFromFile(Path.Combine("Assets/AssetBundles", "AssetBundles"));
        AssetBundleManifest manifest = assetbundle.LoadAsset<AssetBundleManifest>("AssetBundleManifest");
        string[] dependencies = manifest.GetAllDependencies("asset1.a");
        foreach (var dependency in dependencies)
        {
            Debug.Log(Path.Combine("Assets/AssetBundles", dependency));
            //AssetBundle.LoadFromFile(Path.Combine("Assets/AssetBundles", dependency));
        }
    }
}
