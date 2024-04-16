#version 330 core
in vec3 in_position;
in vec3 in_color;
out vec3 out_color;

uniform mat3 u_view_projection;

void main() {
   gl_Position = vec4(u_view_projection * in_position, 1.0);
   out_color = in_color;
}
