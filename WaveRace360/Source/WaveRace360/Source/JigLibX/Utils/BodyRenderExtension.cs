﻿using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using JigLibX.Math;
using JigLibX.Physics;
using JigLibX.Geometry;
using JigLibX.Collision;

namespace JigLibX.Physics
{
    public static class BodyRenderExtensions
    {
        private static List<Vector3> calcCirclePoints(float radius)
        {
            int elementsToCalc = 24;

            float stepSize = -360.0f / elementsToCalc;

            List<Vector3> l = new List<Vector3>();

            for (float slice = 0; slice <= elementsToCalc; slice++)
            {
                double stepRad = MathHelper.ToRadians(slice * stepSize);
                
                float x1 = (float)(System.Math.Sin(stepRad));
                float y1 = (float)(System.Math.Cos(stepRad));

                l.Add(new Vector3(x1, y1, 0) * radius);
            }

            return l;
        }

        private static void AddShapeToWireframe( List<Vector3> shape, List<VertexPositionColor> wireframe, Matrix orientation, Color color )
        {
            if (wireframe.Count > 0)
            {
                Vector3 v = wireframe[wireframe.Count - 1].Position;
                wireframe.Add(new VertexPositionColor(v, new Color(0, 0, 0, 0)));
                wireframe.Add(new VertexPositionColor(shape[0], new Color(0, 0, 0, 0)));
            }

            foreach (Vector3 point in shape)
            {
                wireframe.Add(new VertexPositionColor(Vector3.Transform(point, orientation), color));
            }
        }

        private static void AddLineToWireframe(Vector3 from, Vector3 to, List<VertexPositionColor> wireframe, Matrix orientation, Color color)
        {
            if (wireframe.Count > 0)
            {
                Vector3 v = wireframe[wireframe.Count - 1].Position;
                wireframe.Add(new VertexPositionColor(v, new Color(0, 0, 0, 0)));
                wireframe.Add(new VertexPositionColor(Vector3.Transform(from, orientation), new Color(0, 0, 0, 0)));
            }

            wireframe.Add(new VertexPositionColor(Vector3.Transform(from, orientation), color));
            wireframe.Add(new VertexPositionColor(Vector3.Transform(to, orientation), color));
        }

        private static void AddLinesToWireframe(List<Vector3> points, List<VertexPositionColor> wireframe, Matrix orientation, Color color)
        {
            for (int i = 0; i < points.Count; i += 2)
            {
                AddLineToWireframe(points[i], points[i + 1], wireframe, orientation, color);
            }
        }

        public static VertexPositionColor[] GetBodyWireframe(this Body body)
        {
            List<VertexPositionColor> wireframe = new List<VertexPositionColor>();


            for (int i = 0; i < body.CollisionSkin.NumPrimitives; i++)
            {
                Primitive p = body.CollisionSkin.GetPrimitiveNewWorld(i);

                if (p is Sphere)
                {
                    Sphere np = (Sphere)p;

                    List<Vector3> SpherePoints = calcCirclePoints(np.Radius);

                    AddShapeToWireframe(SpherePoints, wireframe, Matrix.Identity, Color.Blue);
                    AddShapeToWireframe(SpherePoints, wireframe, Matrix.CreateRotationY(MathHelper.PiOver2), Color.Red);
                    AddShapeToWireframe(SpherePoints, wireframe, Matrix.CreateRotationX(MathHelper.PiOver2), Color.Green);

                }
                else if (p is Capsule)
                {
                    Capsule np = (Capsule)p;


                    List<Vector3> Ball = calcCirclePoints(np.Radius);
                    List<Vector3> CylPoints = new List<Vector3>();
                    List<Vector3> CirclePoints = new List<Vector3>();
                    List<Vector3> SidePoints = new List<Vector3>();

                    // Create LongWays profile slice
                    foreach (Vector3 v in Ball)
                    {
                        Vector3 t = Vector3.Transform(v, Matrix.CreateRotationX(MathHelper.PiOver2));

                        CylPoints.Add(t);
                    }

                    float len = np.Length - np.Radius;

                    SidePoints.Add(Vector3.Transform(new Vector3(np.Radius, len, 0), Matrix.CreateRotationX(MathHelper.PiOver2)));
                    SidePoints.Add(Vector3.Transform(new Vector3(np.Radius, -len, 0), Matrix.CreateRotationX(MathHelper.PiOver2)));
                    SidePoints.Add(Vector3.Transform(new Vector3(-np.Radius, -len, 0), Matrix.CreateRotationX(MathHelper.PiOver2)));
                    SidePoints.Add(Vector3.Transform(new Vector3(-np.Radius, len, 0), Matrix.CreateRotationX(MathHelper.PiOver2)));

                    // Create Y Rungs
                    AddShapeToWireframe(Ball, wireframe, Matrix.CreateTranslation(new Vector3(0, 0, len)), Color.Green);
                    AddShapeToWireframe(Ball, wireframe, Matrix.CreateTranslation(new Vector3(0, 0, -len)), Color.Green);
                    AddShapeToWireframe(Ball, wireframe, Matrix.Identity, Color.Green);

                    // Create Z Profile
                    Matrix Zmat = Matrix.CreateRotationZ(MathHelper.PiOver2);
                    AddShapeToWireframe(CylPoints, wireframe, Matrix.CreateTranslation(new Vector3(0, 0, len)) * Zmat, Color.Blue);
                    AddShapeToWireframe(CylPoints, wireframe, Matrix.CreateTranslation(new Vector3(0, 0, -len)) * Zmat, Color.Blue);
                    AddLineToWireframe(SidePoints[0], SidePoints[1], wireframe, Zmat, Color.Blue);
                    AddLineToWireframe(SidePoints[2], SidePoints[3], wireframe, Zmat, Color.Blue);

                    // Create X Profile 
                    Matrix Xmat = Matrix.Identity;
                    AddShapeToWireframe(CylPoints, wireframe, Matrix.CreateTranslation(new Vector3(0, 0, len)) * Xmat, Color.Red);
                    AddShapeToWireframe(CylPoints, wireframe, Matrix.CreateTranslation(new Vector3(0, 0, -len)) * Xmat, Color.Red);
                    AddLineToWireframe(SidePoints[0], SidePoints[1], wireframe, Xmat, Color.Red);
                    AddLineToWireframe(SidePoints[2], SidePoints[3], wireframe, Xmat, Color.Red);

                }
                else if (p is Box)
                {
                    Box np = (Box)p;


                    List<Vector3> xPoints = new List<Vector3>();
                    List<Vector3> yPoints = new List<Vector3>();
                    List<Vector3> zPoints = new List<Vector3>();

                    Vector3 slen = np.GetHalfSideLengths();


                    xPoints.Add(new Vector3(slen.X, slen.Y, slen.Z));
                    xPoints.Add(new Vector3(-slen.X, slen.Y, slen.Z));
                    xPoints.Add(new Vector3(slen.X, -slen.Y, slen.Z));
                    xPoints.Add(new Vector3(-slen.X, -slen.Y, slen.Z));
                    xPoints.Add(new Vector3(slen.X, slen.Y, -slen.Z));
                    xPoints.Add(new Vector3(-slen.X, slen.Y, -slen.Z));
                    xPoints.Add(new Vector3(slen.X, -slen.Y, -slen.Z));
                    xPoints.Add(new Vector3(-slen.X, -slen.Y, -slen.Z));


                    yPoints.Add(new Vector3(slen.X, slen.Y, slen.Z));
                    yPoints.Add(new Vector3(slen.X, -slen.Y, slen.Z));
                    yPoints.Add(new Vector3(-slen.X, slen.Y, slen.Z));
                    yPoints.Add(new Vector3(-slen.X, -slen.Y, slen.Z));
                    yPoints.Add(new Vector3(slen.X, slen.Y, -slen.Z));
                    yPoints.Add(new Vector3(slen.X, -slen.Y, -slen.Z));
                    yPoints.Add(new Vector3(-slen.X, slen.Y, -slen.Z));
                    yPoints.Add(new Vector3(-slen.X, -slen.Y, -slen.Z));

                    zPoints.Add(new Vector3(slen.X, slen.Y, slen.Z));
                    zPoints.Add(new Vector3(slen.X, slen.Y, -slen.Z));
                    zPoints.Add(new Vector3(-slen.X, slen.Y, slen.Z));
                    zPoints.Add(new Vector3(-slen.X, slen.Y, -slen.Z));
                    zPoints.Add(new Vector3(slen.X, -slen.Y, slen.Z));
                    zPoints.Add(new Vector3(slen.X, -slen.Y, -slen.Z));
                    zPoints.Add(new Vector3(-slen.X, -slen.Y, slen.Z));
                    zPoints.Add(new Vector3(-slen.X, -slen.Y, -slen.Z));

                    AddLinesToWireframe(xPoints, wireframe, Matrix.Identity, Color.Red);
                    AddLinesToWireframe(yPoints, wireframe, Matrix.Identity, Color.Green);
                    AddLinesToWireframe(zPoints, wireframe, Matrix.Identity, Color.Blue);
                }
                else if (p is AABox)
                {
                }
                else if (p is Heightmap)
                {
                    Heightmap hm = (Heightmap)p;
                    Vector3 point, normal;

                    for(int e = 0;e<hm.Heights.Nx;e++)
                    {
                        for (int j = 0; j < hm.Heights.Nz; j++)
                        {
                            hm.GetSurfacePosAndNormal(out point, out normal,e,j);
                            AddLineToWireframe(point,point - 0.5f * normal, wireframe, Matrix.Identity, Color.Yellow);
                        }
                    }

                }
                else if (p is JigLibX.Geometry.Plane)
                {                  
                }
                else if (p is TriangleMesh)
                {
                    TriangleMesh np = (TriangleMesh)p;

                    for (int j = 0; j < np.GetNumTriangles(); j++)
                    {
                        IndexedTriangle t = np.GetTriangle(j);

                        Vector3 p1 = np.GetVertex(t.GetVertexIndex(0));
                        Vector3 p2 = np.GetVertex(t.GetVertexIndex(1));
                        Vector3 p3 = np.GetVertex(t.GetVertexIndex(2));

                        List<Vector3> tPoints = new List<Vector3>();

                        tPoints.Add(p1);
                        tPoints.Add(p2);
                        tPoints.Add(p3);
                        tPoints.Add(p1);

                        AddShapeToWireframe(tPoints, wireframe, Matrix.Identity, Color.Red);

                    }
                }

            }

            return wireframe.ToArray();
        }

        public static void TransformWireframe(this Body body, VertexPositionColor[] wireframe)
        {
            
            for ( int i = 0; i < wireframe.Length; i++)
            {
                wireframe[i].Position = Vector3.Transform(wireframe[i].Position,
                                            body.CollisionSkin.GetPrimitiveLocal(0).Transform.Orientation *
                                            body.Orientation *
                                            Matrix.CreateTranslation(body.Position)
                                            );
            }

        }

    }
}
