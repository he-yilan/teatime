#version 330 core

uniform mat3 u_view_projection;

in vec3 in_position;
in vec3 in_normal;

out vec3 v_position;
out vec3 v_normal;

void main() {
  v_position = in_position;
  v_normal = in_normal;
  gl_Position = vec4(u_view_projection * in_position, 1.0);
}
