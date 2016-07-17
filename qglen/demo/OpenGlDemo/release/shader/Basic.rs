<?xml version="1.0" encoding="UTF-8"?>
<rae>
    <FragmentCode>in highp vec4 vColor;
out highp vec4 fColor;
void main() {
   fColor = vColor;
}
</FragmentCode>
    <GeometryCode></GeometryCode>
    <Name>Basic</Name>
    <Version>4097</Version>
    <VertexCode>in vec3 position;
in vec3 color;
out vec4 vColor;
uniform highp mat4 matCamera;
void main() {
   gl_Position = matCamera * vec4(position, 1.0);
   vColor = vec4(color, 1.0);
}
</VertexCode>
</rae>
