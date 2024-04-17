#version 330

uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

in vec3 v_position;
in vec3 v_normal;

out vec3 out_color;

void main() {
  vec3 w_in = u_light_pos - v_position;
  float r = length(w_in);

  out_color = 0.5 * (u_light_intensity / (r * r)) * max(0, dot(v_normal, w_in));
}