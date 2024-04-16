#version 330

uniform vec3 u_cam_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

in vec3 v_position;
in vec3 v_normal;

out vec3 out_color;

void main() {
  //General Purpose
  vec3 w_in = u_light_pos - v_position;
  float r = length(w_in);

  //Diffuse Lighting
  float k_d = 0.5; // diffuse coefficient
  vec3 l_diffuse = k_d * (u_light_intensity / (r * r)) * max(0, dot(v_normal, w_in));

  //Ambient Lighting
  float k_a = 0.2; //ambient coefficient
  vec3 I_a = vec3(0.5,0.5,0.5); //ambient light intensity
  vec3 l_ambient = k_a * I_a;

  //Specular Lighting
  //k_s = 0.5, p = 20 --> not bad!
  float k_s = 0.75; //specular coefficient
  float p = 15; //how many times we amplify specular highlights??
  vec3 w_out = u_cam_pos - v_position;
  vec3 h = (w_in + w_out) / length(w_in + w_out);
  vec3 l_specular = k_s * (u_light_intensity / (r * r)) * pow(max(0, dot(v_normal, h)), p);

  out_color = l_ambient + l_diffuse + l_specular;
}
