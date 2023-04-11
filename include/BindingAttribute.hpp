

namespace SoftRender {
enum Vertex_Buffer_Type {
  position,
  color,
  uv,
  normal
};
struct BindingAttr {
    Vertex_Buffer_Type type;
    // int buffer_index;
    int offset;
    int size;
};
}