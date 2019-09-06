using System.IO;
using UnityEngine;

public class LoadAsset : MonoBehaviour
{
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            var assetbundle = AssetBundle.LoadFromFile(Path.Combine("Assets/AssetBundles", "a.a"));
            var gameObject = assetbundle.LoadAsset<GameObject>("prefab1");
            Instantiate(gameObject);
        }
        if (Input.GetKeyDown(KeyCode.W)
        {
            var assetbundle = AssetBundle.LoadFromFile(Path.Combine("Assets/AssetBundles", "a.a"));
            AssetBundleManifest manifest = assetbundle.LoadAsset<AssetBundleManifest>()
        }
    }
}
