#version 330

in vec3 v_position;
in vec3 v_normal;

out vec3 out_color;

void main() {
  out_color = (vec3(1, 1, 1) + v_normal) / 2;
}
