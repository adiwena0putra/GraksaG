import QtQuick 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.12
import Qt3D.Extras 2.12

Entity{
    id: root_scene
    property alias x_rot: payload_transform.rotationX
    property alias y_rot: payload_transform.rotationY
    property alias z_rot: payload_transform.rotationZ

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 180.0, 180.0, 180.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    components: [
        RenderSettings{
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }

        }
    ]

    GoochMaterial{
        id: payload_material
    }

    Mesh{
        id: payload_mesh
        source: "3D/Payload.stl"
    }

    Transform{
        id: payload_transform
    }

    Entity{
        id: payload_entity
        components: [payload_mesh, payload_material, payload_transform]
    }

    Connections{
        target: obj_ModelAttitude
        onUpdate_UI: {
            payload_transform.rotationX = pitch;
            payload_transform.rotationY = yaw;
            payload_transform.rotationZ = roll;
        }
    }

}
