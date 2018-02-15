#include <Catch/catch.hpp>

#include <Content/OBJModelLoader.h>
#include <Math/Vector3.h>

using namespace Gene::Content;
using namespace Gene;

TEST_CASE("Test load vertices from obj file", "[OBJModelLoader]")
{
    const char *obj = "v 1.0 0.55 0.085\n"
                      "v 1.6 0.11 0.977\n";

    OBJModelLoader modelLoader;
    GeneModel *model = modelLoader.LoadFromMemory(obj);

    Vector3 vertex1 = model->Vertices[0];
    Vector3 vertex2 = model->Vertices[1];

    REQUIRE(vertex1.X == Approx(1.0));
    REQUIRE(vertex1.Y == Approx(0.55));
    REQUIRE(vertex1.Z == Approx(0.085));
}
