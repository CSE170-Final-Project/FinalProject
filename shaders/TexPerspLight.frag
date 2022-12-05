#version 400

in vec3 vert_Pos;
in vec3 vert_Normal;
in vec3 vert_TexCoord;

out vec4 frag_Color;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform sampler2DArray texID;

vec4 shade( void )
{
	vec4 la = vec4( 0.1, 0.1, 0.1, 1.0 );
	vec4 ld = vec4( 0.9, 0.9, 0.9, 1.0 );
	vec4 ls = vec4( 1.0, 1.0, 1.0, 1.0 );

	vec4 ka;
	vec4 kd;

	ka = texture(texID, vert_TexCoord);
	kd = texture(texID, vert_TexCoord);
	// ka = vec4(1, 1, 1, 1);
	// kd = vec4(1, 1, 1, 1);
	
	vec4 ks = vec4( 1.0, 1.0, 1.0, 1.0 ); // closeLightColor;

	float shininess = 16.0f; // shininess;

	mat4 transf = viewMatrix * modelMatrix;

	vec3 FragPos  = vec3( transf * vec4(vert_Pos,1) );
	vec3 FragNorm = mat3( transpose( inverse( transf ) ) ) * vert_Normal.xyz;
	vec3 closeLightPos = vec3( transf * vec4( 3.0, 3.0, 3.0, 1.0 ) );
	vec3 farLightDir = normalize(vec3( transf * vec4(vec3(-1, 3, -1), 0.0)));

	vec3 N = normalize( FragNorm ); // vertex normal
	vec3 L = normalize( closeLightPos - FragPos ); // light direction
	vec3 R = normalize( reflect( -L, N ) ); // reflected ray
	vec3 V = normalize( vec3( 0.0, 0.0, 1.0 ) ); // view direction

	vec4 farLightColor = vec4(1.0, 0.9, 0.1, 1.0);

	float dotLN = dot( L, N );
	vec4 amb = ka * la; // dark color
	vec4 close_dif = kd * ld * max( dotLN, 0.0 ); // diffuse color from close light source
	vec4 close_spe = ks * ls * pow( max( dot( V, R ), 0.0 ), shininess ) * max( dotLN, 0.0 ); // diffuse color from close light source
	vec4 far_dif = kd * ld * max( dot(N, farLightDir), 0.0 ); // diffuse color from close light source
	vec4 far_spe = farLightColor * ls * pow( max( dot( V, normalize(reflect(farLightDir, N)) ), 0.0 ), shininess ) * max( dot(N, farLightDir), 0.0 ); // diffuse color from close light source

	return amb + close_dif + close_spe + far_dif + far_spe;
	// return vert_Color;
	// return vec4(1,1,1,1);
}

void main( void )
{
	vec4 col = shade();
	if(col.w < 0.5) discard;
	else frag_Color = col;
	// frag_Color = vec4(1,1,1,1);
}
