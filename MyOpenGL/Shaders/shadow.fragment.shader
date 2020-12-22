#version 400

void main() {
    gl_FragDepth = gl_FragCoord.z; // this could be commented-out since its expected default behavior
}