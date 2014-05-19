#include "Cube.hpp"

Cube::Cube()
{
}

Cube::~Cube()
{

}

bool Cube::initialize()
{
  glm::vec3 vertice[] = {
    glm::vec3(1.000000, -1.000000, -1.000000),
    glm::vec3(1.000000, -1.000000, 1.000000),
    glm::vec3(-1.000000, -1.000000, 1.000000),
    glm::vec3(-1.000000, -1.000000, -1.000000),
    glm::vec3(1.000000, 1.000000, -1.000000),
    glm::vec3(1.000000, 1.000000, 1.000000),
    glm::vec3(-1.000000, 1.000000, 1.000000),
    glm::vec3(-1.000000, 1.000000, -1.000000)
  };

  glm::vec2 uv[] = {
    glm::vec2(0.000000, 0.000000),
    glm::vec2(1.000000, 0.000000),
    glm::vec2(1.000000, 1.000000),
    glm::vec2(0.000000, 1.000000)
  };

  glm::vec3 normals[] = {
    glm::vec3(0.000000, 0.000000, -1.000000),
    glm::vec3(-1.000000, -0.000000, -0.000000),
    glm::vec3(-0.000000, -0.000000, 1.000000),
    glm::vec3(-0.000001, 0.000000, 1.000000),
    glm::vec3(1.000000, -0.000000, 0.000000),
    glm::vec3(1.000000, 0.000000, 0.000001),
    glm::vec3(0.000000, 1.000000, -0.000000),
    glm::vec3(-0.000000, -1.000000, 0.000000)
  };


  _geometry.pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
  _geometry.pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
  _geometry.pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
  _geometry.pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
  _geometry.pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
  _geometry.pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);

  _geometry.pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
  _geometry.pushVertex(vertice[6]).pushUv(uv[1]).pushNormal(normals[1]);
  _geometry.pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
  _geometry.pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
  _geometry.pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
  _geometry.pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[1]);

  _geometry.pushVertex(vertice[1]).pushUv(uv[0]).pushNormal(normals[2]);
  _geometry.pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[2]);
  _geometry.pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[2]);
  _geometry.pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[3]);
  _geometry.pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[3]);
  _geometry.pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[3]);

  _geometry.pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[4]);
  _geometry.pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[4]);
  _geometry.pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[4]);
  _geometry.pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[5]);
  _geometry.pushVertex(vertice[5]).pushUv(uv[2]).pushNormal(normals[5]);
  _geometry.pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[5]);

  _geometry.pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[6]);
  _geometry.pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
  _geometry.pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);
  _geometry.pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
  _geometry.pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[6]);
  _geometry.pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);

  _geometry.pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
  _geometry.pushVertex(vertice[1]).pushUv(uv[1]).pushNormal(normals[7]);
  _geometry.pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
  _geometry.pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
  _geometry.pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
  _geometry.pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[7]);

  _geometry.build();
  return (true);
}

void Cube::draw(gdl::AShader *shader, UNUSED const gdl::Clock& clock)
{
  _geometry.draw(*shader, getTransformation(), GL_TRIANGLES);
}
