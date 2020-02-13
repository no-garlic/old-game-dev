#if XBOX
vs.1.1

m4x4 oPos, v0, c0
mov oT0, v2

#else
vs_1_1

dcl_position v0
dcl_normal v1
dcl_texcoord v2

dp4 oPos.x, v0, c0
dp4 oPos.y, v0, c1
dp4 oPos.z, v0, c2
dp4 oPos.w, v0, c3

mov oT0, v2
#endif