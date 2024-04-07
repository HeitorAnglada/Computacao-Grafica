using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlipperScript : MonoBehaviour
{
    public float restPosition = 0f; // A posição de descanso do flipper
    public float pressedPosition = 45f; // A posição quando o flipper é pressionado
    public float hitStrenght = 100000f; // A força aplicada ao flipper
    public float flipperDamper = 150f; // O amortecimento aplicado ao movimento do flipper
    private HingeJoint2D hinge; 
    public KeyCode flipperKey = KeyCode.D; // A tecla usada para controlar o flipper

    void Start()
    {
        // Obter o componente HingeJoint2D
        hinge = GetComponent<HingeJoint2D>();
        hinge.useMotor = true; // Ativar o motor para movimentar o flipper

        // Configurar os limites do HingeJoint2D
        JointAngleLimits2D limits = hinge.limits;
        limits.min = restPosition;
        limits.max = pressedPosition;
        hinge.limits = limits;
        hinge.useLimits = true;
    }

    void Update()
    {
        // Checar se a tecla D está sendo pressionada
        if (Input.GetKey(flipperKey))
        {
            MoveFlipper(pressedPosition);
        }
        else
        {
            MoveFlipper(restPosition);
        }
    }

    void MoveFlipper(float targetPosition)
    {
        // Calcular a direção necessária para mover o flipper
        float direction = targetPosition == pressedPosition ? 1 : -1;

        // Configurar o motor baseado na direção e na força desejada
        JointMotor2D motor = hinge.motor;
        motor.motorSpeed = direction * hitStrenght;
        motor.maxMotorTorque = flipperDamper;
        hinge.motor = motor;
    }
}
