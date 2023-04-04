#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include <memory>

namespace SoftRender {
class Shader {
public:
    Shader(Mat44<float> model_matrix, Mat44<float> view_matrix, Mat44<float> project_matrix, Mat44<float> screen_matrix);
    ~Shader();
    Point3D vertex_shader(int vertex_index);
    void fragment_shader();
 

private:
    Mat44<float> model_matrix  ;
    Mat44<float> view_matrix  ;
    Mat44<float> project_matrix  ;
    Mat44<float> screen_matrix  ;
};

}