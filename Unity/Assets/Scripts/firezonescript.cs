using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class firezonescript : MonoBehaviour
{
    [SerializeField]
    GameObject RPI;
   // pubRvizTemp script;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

    }
    private void OnTriggerEnter(Collider other)
    {
        //  var tempSensor = other.gameObject.TryGetComponent<pubRvizTemp>();
        //  script.temp = 120;
        RPI.GetComponent<pubRvizTemp>().temp = 120;
    }
    private void OnTriggerExit (Collider other)
    {
        //  var tempSensor = other.gameObject.TryGetComponent<pubRvizTemp>();
        //  script.temp = 120;
        RPI.GetComponent<pubRvizTemp>().temp = 35;
    }
}
