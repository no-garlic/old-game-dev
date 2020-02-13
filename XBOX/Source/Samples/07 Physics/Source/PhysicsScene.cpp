
#include "PhysicsScene.h"


PhysicsScene::PhysicsScene()
{
  m_CameraDist  = 100.0f;
  m_CameraPitch = -30.0f;
}


PhysicsScene::~PhysicsScene()
{
}


bool PhysicsScene::Init()
{
  if (!Physics.Init())
    return false;

  Physics.SetGravity(Vec3(0.0f, -9.81f, 0.0f));

  Physics.AddPlane(Plane(0.0f, 1.0f, 0.0f, 0.0f));

  if (!CreateScene())
    return false;

  return true;
}


void PhysicsScene::Update(float deltaTime)
{
  PreUpdateScene();

  // Max timestep is 1/20 seconds, so update the physics in
  // iterations if the frame time was large than expected.
  while (deltaTime > 0.05f)
  {
    Physics.Update(0.05f);
    deltaTime -= 0.05f;
  }
  Physics.Update(deltaTime);

  PostUpdateScene();
}



void PhysicsScene::Cull()
{
  m_pSceneNode->Cull(m_RenderList, Camera.GetFrustum());
}


void PhysicsScene::Render()
{
  m_RenderList.Render(m_Lights);
  Physics.Render();
}


void PhysicsScene::SetRenderState()
{
  m_Lights.clear();

  DirectionalLight *pLight = new DirectionalLight(Vec3(0.5f, -0.7f, 0.7f));
  Device->SetLight(0, pLight);
  Device->LightEnable(0, TRUE);
  RenderState.Set(D3DRS_LIGHTING, TRUE);

  m_Lights.push_back(pLight);
}


void PhysicsScene::Resize()
{
  // Get the aspect ratio of the main window
  float aspect = Application.CalculateAspectRatio();
  float fov = 45.0f;

  // Set the global camera perspective projection (proj matrix)
  Camera.SetProjPerspective(fov, aspect, 1.0f, 5000.0f);

  // Set the global camera lookat vectors (view matrix)
  Vec3 eye = Vec3(0.0f, 600.0f, -300.0f);
  Vec3  at = Vec3(0.0f, 0.0f, 0.0f);
  Vec3  up(0.0f, 1.0f, 0.0f);
  Camera.LookAt(eye, at, up);
}


bool PhysicsScene::CreateScene()
{
  m_pSceneNode = new SceneNode();

  // Create an object
  if (!CreateObject("Floor", "Floor_300.msh", Vec3(0.0f, 0.0f, 0.0f)))
    return false;

  //if (!CreateObject("Wall_1", "Wall_300.msh", Vec3(-1500.0f, 0.0f, 0.0f)))
  //  return false;

  //if (!CreateObject("Wall_2", "Wall_300.msh", Vec3(150.0f, 00.0f, 0.0f)))
  //  return false;

  /*
  if (!CreateObject("Wall_3", "Wall_300.msh", Vec3(30.0f, 30.0f, -30.0f)))
    return false;

  if (!CreateObject("Wall_4", "Wall_300.msh", Vec3(30.0f, 30.0f, -30.0f)))
    return false;
  */

  if (!CreateObject("Player", "Player.msh", Vec3(0.0f, 180.0f, 0.0f)))
    return false;

  for (uint i = 0; i < 20; i++)
  {
    String name = "Box_";
    AppendInt(name, i);

    if (!CreateObject(name, "Box.msh", Vec3(FloatRandom(-1400.0f, 1400.0f), FloatRandom(100.0f, 200.0f), FloatRandom(-1400.0f, 1400.0f))))
      return false;
  }


  return true;
}


bool PhysicsScene::CreateObject(const String &name, const String &mesh, const Vec3 &startPos)
{
  // Create an object
  PhysicsScene::PhysicalObject object;

  // Load the mesh
  FileHandle handle = Application.GetModelDatabase()->FindFileHandle(mesh);
  object.m_pMesh = (IndexedMesh *) MeshLoader::LoadMesh(handle);
  if (!object.m_pMesh)
    return false;

  // Set the initial position (10x the radius above the ground)
  object.m_Matrix = Matrix::MakeNewTranslation(startPos);
  
  if (name == "Player")
  {
    // Create the physics
    object.m_pBody = new RigidBodyDynamicBox();
    if (!((RigidBodyDynamicBox*)object.m_pBody)->Init(object.m_pMesh->GetBBox().GetSize()))
      return false;
    object.m_pBody->SetMatrix(object.m_Matrix);
    ((RigidBodyDynamic*)object.m_pBody)->SetMass(50.0f);
  }
  else if (name == "Floor" || name == "Wall_1" || name == "Wall_2")
  {
    // Create the physics
    Box box = object.m_pMesh->GetBBox();
    object.m_pBody = new RigidBodyStaticBox();
    ((RigidBodyStaticBox*)object.m_pBody)->Init(box.GetSize());
    object.m_pBody->SetMatrix(object.m_Matrix);
  }
  else
  {
    // Create the physics
    object.m_pBody = new RigidBodyDynamicBox();
    if (!((RigidBodyDynamicBox*)object.m_pBody)->Init(object.m_pMesh->GetBBox().GetSize()))
      return false;
    object.m_pBody->SetMatrix(object.m_Matrix);
    ((RigidBodyDynamic*)object.m_pBody)->SetMass(10.0f);
  }
  
  // Create the scenegraph nodes
  object.m_pMeshNode = new MeshNode();
  object.m_pTransformNode = new TransformNode();

  // Add the mesh to the scenegraph
  object.m_pMeshNode->AddMesh(object.m_pMesh);
  object.m_pTransformNode->AddChild(object.m_pMeshNode);
  m_pSceneNode->AddChild(object.m_pTransformNode);

  // Set the object matrix
  object.m_pTransformNode->SetTransform(object.m_Matrix);

  // Add the object to the array
  m_Objects[name] = object;
  return true;
}


void PhysicsScene::PreUpdateScene()
{
  float yAxis = Input.GetGamepadAxisValue(GAMEPAD_AXIS_LEFT_Y);
  float xAxis = Input.GetGamepadAxisValue(GAMEPAD_AXIS_LEFT_X);

  if (fabs(xAxis) > 0.2f || fabs(yAxis) > 0.2f)
  {
    float force = 5000.0f;

    PhysicsScene::PhysicalObject &obj = m_Objects["Player"];
    ((RigidBodyDynamic*)obj.m_pBody)->AddForce(Vec3(xAxis * force, 0.0f, yAxis * force));
  }

  static bool isDown = false;
  if (Input.GetGamepadButtonState(GAMEPAD_BUTTON_A) == GAMEPADVAL_DOWN)
  {
    if (!isDown)
    {
      isDown = true;

      PhysicsScene::PhysicalObject &obj = m_Objects["Player"];
      ((RigidBodyDynamic*)obj.m_pBody)->AddForce(Vec3(0.0f, 500000.0f, 0.0f));
    }
  }
  else
  {
    isDown = false;
  }

  /*
  // Get a ray from the camera position to the mouse pointer's 3d location
  Ray ray = Camera.GetMouseRay3D();

  // Create a physics ray
  PhysicsManager::Ray physicsRay;
  physicsRay.Position  = ray.GetPosition();
  physicsRay.Direction = ray.GetDirection();
  physicsRay.Length    = 200.0f;

  // Cast the ray
  PhysicsManager::RayHit hit;
  if (Physics.CastRay(physicsRay, hit))
  {
    DEBUG_SPHERE(Sphere(hit.Position, 0.5f), Color::Yellow, 1);
    DEBUG_LINE(LineSegment(hit.Position, hit.Position + (hit.Normal * 20.0f)), Color::Cyan, 1);
  }
  */

  UpdateCamera();
}


void PhysicsScene::UpdateCamera()
{
  float xAxis2 = Input.GetGamepadAxisValue(GAMEPAD_AXIS_RIGHT_X);
  if (fabs(xAxis2) > 0.2f)
  {
  }
  /*
  if (Input.GetGamepadButtonState(GAMEPAD_BUTTON_L1) == GAMEPADVAL_DOWN)
  {
    Camera.SetPosition(Camera.GetPosition() + Camera.GetUp() * Application.GetFrameTime() * -300.0f);
  }
  if (Input.GetGamepadButtonState(GAMEPAD_BUTTON_R1) == GAMEPADVAL_DOWN)
  {
    Camera.SetPosition(Camera.GetPosition() + Camera.GetUp() * Application.GetFrameTime() * 300.0f);
  }
  */


  // Test camera collision
  Matrix cameraMatrix = MatrixIdentity;
  cameraMatrix.SetTAxis(Camera.GetPosition());
  if (Physics.IsSpherePenetrating(30.0f, cameraMatrix, PhysicsManager::COLLIDE_STATIC_GEOM | PhysicsManager::COLLIDE_DYNAMIC_GEOM))
  {
    //::Beep(7500, 1);
  }
}


void PhysicsScene::PostUpdateScene()
{
  Map<String, PhysicalObject>::iterator iter(m_Objects.begin()), end(m_Objects.end());
  for (; iter != end; ++iter)
  {
    PhysicsScene::PhysicalObject &object = iter->second;
    object.m_pBody->GetMatrix(object.m_Matrix);
    object.m_pTransformNode->SetTransform(object.m_Matrix);
  }
}


// -- EOF


