#include "m1/vector.hpp"
#include "catch.hpp"

template class m1::vector<bool[4]>;
template class m1::vector<int[4]>;
template class m1::vector<float[4]>;
template class m1::vector<double[4]>;

template <typename T> struct print_type;

constexpr const m1::index_constant<0> x{};
constexpr const m1::index_constant<1> y{};
constexpr const m1::index_constant<2> z{};
constexpr const m1::index_constant<3> w{};

constexpr float test_dot(m1::vector3f const &lhs, m1::vector3f const &rhs) noexcept
{
    return lhs.data[0] * rhs.data[0] +
           lhs.data[1] * rhs.data[1] +
           lhs.data[2] * rhs.data[2];
}

template <typename T>
void TestVectorStructure(m1::vector<T> const &v)
{
    CHECK(&v.x() == &v[0]);
    CHECK(&v.y() == &v[1]);
    CHECK(&v.z() == &v[2]);

    CHECK(&v.x() == &v[x]);
    CHECK(&v.y() == &v[y]);
    CHECK(&v.z() == &v[z]);

    CHECK(&v.x() == &v.at(0));
    CHECK(&v.y() == &v.at(1));
    CHECK(&v.z() == &v.at(2));
    CHECK_THROWS(v.at(3));

    CHECK(&v.x() == &v.at(x));
    CHECK(&v.y() == &v.at(y));
    CHECK(&v.z() == &v.at(z));

    CHECK(&v.x() == &v.data[0]);
    CHECK(&v.y() == &v.data[1]);
    CHECK(&v.z() == &v.data[2]);
}

template <typename T>
void TestVectorStructure(m1::vector<T> &v)
{
    CHECK(&v.x() == &v[0]);
    CHECK(&v.y() == &v[1]);
    CHECK(&v.z() == &v[2]);

    CHECK(&v.x() == &v[x]);
    CHECK(&v.y() == &v[y]);
    CHECK(&v.z() == &v[z]);

    CHECK(&v.x() == &v.at(0));
    CHECK(&v.y() == &v.at(1));
    CHECK(&v.z() == &v.at(2));
    CHECK_THROWS(v.at(3));

    CHECK(&v.x() == &v.at(x));
    CHECK(&v.y() == &v.at(y));
    CHECK(&v.z() == &v.at(z));

    CHECK(&v.x() == &v.data[0]);
    CHECK(&v.y() == &v.data[1]);
    CHECK(&v.z() == &v.data[2]);

    TestVectorStructure(const_cast<m1::vector<T> const&>(v));
}

TEST_CASE("Test m1::vector", "[m1]")
{
    static_assert(std::is_pod<m1::vector2b>::value, "is_pod");
    static_assert(std::is_pod<m1::vector3b>::value, "is_pod");
    static_assert(std::is_pod<m1::vector4b>::value, "is_pod");
    static_assert(std::is_pod<m1::vector2i>::value, "is_pod");
    static_assert(std::is_pod<m1::vector3i>::value, "is_pod");
    static_assert(std::is_pod<m1::vector4i>::value, "is_pod");
    static_assert(std::is_pod<m1::vector2f>::value, "is_pod");
    static_assert(std::is_pod<m1::vector3f>::value, "is_pod");
    static_assert(std::is_pod<m1::vector4f>::value, "is_pod");
    static_assert(std::is_pod<m1::vector2d>::value, "is_pod");
    static_assert(std::is_pod<m1::vector3d>::value, "is_pod");
    static_assert(std::is_pod<m1::vector4d>::value, "is_pod");

    using m1::vector3b;
    using m1::vector3i;
    using m1::vector3f;

    {
        vector3f v; // uninitialized
        TestVectorStructure(v);
    }

    {
        vector3f v = {}; // aggregate initialization

        CHECK(v.x() == Approx(0.0f));
        CHECK(v.y() == Approx(0.0f));
        CHECK(v.z() == Approx(0.0f));

        TestVectorStructure(v);
    }

    {
        vector3f v(1.0f, 2.0f, 3.0f); // variadic constructor
        CHECK(v.x() == Approx(1.0f));
        CHECK(v.y() == Approx(2.0f));
        CHECK(v.z() == Approx(3.0f));

        TestVectorStructure(v);
    }

    {
        constexpr vector3i const v = {1, 2, 3}; // variadic constructor
        static_assert(v.x() == 1, "1");
        static_assert(v.y() == 2, "2");
        static_assert(v.z() == 3, "3");

        TestVectorStructure(v);
    }

    {

        typedef m1::vector<vector3f::data_type&> vectorR3f;
        float data[3] = {2.0f, 4.0f, 6.0f};

        vectorR3f vref(data);
        static_assert(std::is_reference<decltype(vref[0])>::value, "is_const");
        static_assert(!std::is_const<std::remove_reference_t<decltype(vref[0])>>::value, "!is_const");

        CHECK(&vref.data == &data);

        TestVectorStructure(vref);
    }

    {
        float data[3] = {2.0f, 4.0f, 6.0f};

        auto vref = m1::make_vector_ref(data);

        static_assert(std::is_reference<decltype(vref[0])>::value, "is_reference");
        static_assert(std::is_same<decltype(vref)::data_type, decltype(data)&>::value, "is_same");

        CHECK(&vref.data == &data);

        TestVectorStructure(vref);
    }

    {
        float data[3] = {2.0f, 4.0f, 6.0f};

        auto vref = m1::make_vector_cref(data);

        static_assert(std::is_reference<decltype(vref[0])>::value, "is_reference");
        static_assert(std::is_const<std::remove_reference_t<decltype(vref[0])>>::value, "is_const");
        static_assert(std::is_same<decltype(vref)::data_type, decltype(data) const&>::value, "is_same");

        CHECK(&vref.data == &data);

        TestVectorStructure(vref);
    }

    {
        vector3f const v = m1::make_vector(1.0f, 2.0f, 3.0f);
        CHECK(v.x() == Approx(1.0f));
        CHECK(v.y() == Approx(2.0f));
        CHECK(v.z() == Approx(3.0f));
    }

    {
        vector3f const v = {1.0f, 2.0f, 3.0f};

        vector3f u = v;
        CHECK(u[0] == Approx(v[0]));
        CHECK(u[1] == Approx(v[1]));
        CHECK(u[2] == Approx(v[2]));

        u += v;
        CHECK(u[0] == Approx(v[0] + v[0]));
        CHECK(u[1] == Approx(v[1] + v[1]));
        CHECK(u[2] == Approx(v[2] + v[2]));

        u -= v;
        CHECK(u[0] == Approx(v[0]));
        CHECK(u[1] == Approx(v[1]));
        CHECK(u[2] == Approx(v[2]));

        u *= 2.0f;
        CHECK(u[0] == Approx(2.0f * v[0]));
        CHECK(u[1] == Approx(2.0f * v[1]));
        CHECK(u[2] == Approx(2.0f * v[2]));

        u /= 2.0f;
        CHECK(u[0] == Approx(v[0]));
        CHECK(u[1] == Approx(v[1]));
        CHECK(u[2] == Approx(v[2]));

        vector3f const pos_v = +v;
        CHECK(pos_v[0] == Approx(+v[0]));
        CHECK(pos_v[1] == Approx(+v[1]));
        CHECK(pos_v[2] == Approx(+v[2]));

        vector3f const neg_v = -v;
        CHECK(neg_v[0] == Approx(-v[0]));
        CHECK(neg_v[1] == Approx(-v[1]));
        CHECK(neg_v[2] == Approx(-v[2]));

        vector3f const add = u + v;
        CHECK(add[0] == Approx(u[0] + v[0]));
        CHECK(add[1] == Approx(u[1] + v[1]));
        CHECK(add[2] == Approx(u[2] + v[2]));

        vector3f const sub = u - v;
        CHECK(sub[0] == Approx(u[0] - v[0]));
        CHECK(sub[1] == Approx(u[1] - v[1]));
        CHECK(sub[2] == Approx(u[2] - v[2]));

        vector3f const mul1 = u * 4.0f;
        CHECK(mul1[0] == Approx(u[0] * 4.0f));
        CHECK(mul1[1] == Approx(u[1] * 4.0f));
        CHECK(mul1[2] == Approx(u[2] * 4.0f));

        vector3f const mul2 = 3.0f * u;
        CHECK(mul2[0] == Approx(3.0f * u[0]));
        CHECK(mul2[1] == Approx(3.0f * u[1]));
        CHECK(mul2[2] == Approx(3.0f * u[2]));

        vector3f const div = u / 5.0f;
        CHECK(div[0] == Approx(u[0] / 5.0f));
        CHECK(div[1] == Approx(u[1] / 5.0f));
        CHECK(div[2] == Approx(u[2] / 5.0f));

        vector3i const i = {0, 1, 2};
        vector3b const not1 = !i;
        CHECK(not1[0] == true);
        CHECK(not1[1] == false);
        CHECK(not1[2] == false);

        vector3i const b = {true, false, true};
        vector3b const not2 = !b;
        CHECK(not2[0] == false);
        CHECK(not2[1] == true);
        CHECK(not2[2] == false);

        vector3b const and1 = not1 && not2;
        CHECK(and1[0] == false);
        CHECK(and1[1] == false);
        CHECK(and1[2] == false);

        vector3b const and2 = not1 && b;
        CHECK(and2[0] == true);
        CHECK(and2[1] == false);
        CHECK(and2[2] == false);

        vector3b const less = (u < 2.0f * v);
        CHECK(less[0] == true);
        CHECK(less[1] == true);
        CHECK(less[2] == true);

        vector3b const lequal = (u <= 2.0f * v);
        CHECK(lequal[0] == true);
        CHECK(lequal[1] == true);
        CHECK(lequal[2] == true);

        vector3b const greater = (u > 2.0f * v);
        CHECK(greater[0] == false);
        CHECK(greater[1] == false);
        CHECK(greater[2] == false);

        vector3b const gequal = (u >= 2.0f * v);
        CHECK(gequal[0] == false);
        CHECK(gequal[1] == false);
        CHECK(gequal[2] == false);

        vector3i const j = {0, 2, 2};
        vector3b const equal = i == j;
        CHECK(equal[0] == true);
        CHECK(equal[1] == false);
        CHECK(equal[2] == true);

        vector3b const nequal = i != j;
        CHECK(nequal[0] == false);
        CHECK(nequal[1] == true);
        CHECK(nequal[2] == false);

        vector3i bitand_assign = i;
        bitand_assign &= j;
        CHECK(bitand_assign[0] == (i[0] & j[0]));
        CHECK(bitand_assign[1] == (i[1] & j[1]));
        CHECK(bitand_assign[2] == (i[2] & j[2]));

        vector3i bitor_assign = i;
        bitor_assign |= j;
        CHECK(bitor_assign[0] == (i[0] | j[0]));
        CHECK(bitor_assign[1] == (i[1] | j[1]));
        CHECK(bitor_assign[2] == (i[2] | j[2]));

        vector3i bitxor_assign = i;
        bitxor_assign ^= j;
        CHECK(bitxor_assign[0] == (i[0] ^ j[0]));
        CHECK(bitxor_assign[1] == (i[1] ^ j[1]));
        CHECK(bitxor_assign[2] == (i[2] ^ j[2]));

        vector3i const bit_not = ~i;
        CHECK(bit_not[0] == ~i[0]);
        CHECK(bit_not[1] == ~i[1]);
        CHECK(bit_not[2] == ~i[2]);

        vector3i const bit_and = i & j;
        CHECK(bit_and[0] == (i[0] & j[0]));
        CHECK(bit_and[1] == (i[1] & j[1]));
        CHECK(bit_and[2] == (i[2] & j[2]));

        vector3i const bit_or = i | j;
        CHECK(bit_or[0] == (i[0] | j[0]));
        CHECK(bit_or[1] == (i[1] | j[1]));
        CHECK(bit_or[2] == (i[2] | j[2]));

        vector3i const bit_xor = i ^ j;
        CHECK(bit_xor[0] == (i[0] ^ j[0]));
        CHECK(bit_xor[1] == (i[1] ^ j[1]));
        CHECK(bit_xor[2] == (i[2] ^ j[2]));
    }

    {
       vector3f const u = {0.8f, 0.6f, 0.0f};
       CHECK(length(u) == Approx(1.0f));

       vector3f const v = {-0.5f, 0.5f, 0.0f};
       float const u_dot_v = test_dot(u, v);
       CHECK(u_dot_v == Approx(u[0] * v[0] + u[1] * v[1] + u[2] * v[2]));

       vector3f const u2 = normalize(2.5f * u);
       CHECK(u2[0] == Approx(u[0]));
       CHECK(u2[1] == Approx(u[1]));
       CHECK(u2[2] == Approx(u[2]));

       vector3f const unit_x = {1.0f, 0.0f, 0.0f};
       vector3f const unit_y = {0.0f, 1.0f, 0.0f};
       vector3f const unit_z = {0.0f, 0.0f, 1.0f};

       vector3f const x_cross_y = cross(unit_x, unit_y);
       CHECK(x_cross_y[0] == Approx(unit_z[0]));
       CHECK(x_cross_y[1] == Approx(unit_z[1]));
       CHECK(x_cross_y[2] == Approx(unit_z[2]));

       vector3f const z_cross_x = cross(unit_z, unit_x);
       CHECK(z_cross_x[0] == Approx(unit_y[0]));
       CHECK(z_cross_x[1] == Approx(unit_y[1]));
       CHECK(z_cross_x[2] == Approx(unit_y[2]));

       float const sqdist = squared_distance(unit_x, unit_y);
       CHECK(sqdist == Approx(2.0f));

       float const invdist = inverse_distance(unit_x, unit_y);
       CHECK(invdist == Approx(1.0f / m1::sqrt(2.0f)));

       float const dist = distance(unit_x, unit_y);
       CHECK(dist == Approx(m1::sqrt(2.0f)));

       vector3f const u_proj_x = project(u, unit_x);
       CHECK(u_proj_x[0] == Approx(0.8f));
       CHECK(u_proj_x[1] == Approx(0.0f));
       CHECK(u_proj_x[2] == Approx(0.0f));

       vector3f const u_reflect_y = reflect(u, unit_y);
       CHECK(u_reflect_y[0] == Approx( 0.8f));
       CHECK(u_reflect_y[1] == Approx(-0.6f));
       CHECK(u_reflect_y[2] == Approx( 0.0f));

       vector3b const select_condition = u_reflect_y == vector3f{0.0f, 0.0f, 0.0f};
       vector3f const select_u_v = select(select_condition, u, v);
       CHECK(select_u_v[0] == Approx(v[0]));
       CHECK(select_u_v[1] == Approx(v[1]));
       CHECK(select_u_v[2] == Approx(u[2]));
    }

    {
        float s = 0.0f;
        vector3b b = {};
        vector3i i = {};
        vector3f p = {};
        vector3i const j = {1, 2, 4};
        vector3f const t = {0.6f, 0.8f, 2.0f};
        vector3f const u = {0.7f, 0.2f, 0.0f};
        vector3f const v = {0.8f, 0.6f, 1.0f};

        p = abs(u);
        p = acos(u);
        p = asin(u);
        p = atan(u);
        p = ceil(u);
        p = clamp(t, u, v);
        p = clamp(u, 0.2f, 0.6f);
        p = cos(u);
        p = cosh(u);
        p = degrees(u);
        p = exp(v);
        p = exp2(v);
        p = exp10(v);
        p = floor(u);
        p = fract(u);
        p = frexp(t, &i);
        p = inverse_lerp(0.1f, 0.8f, t);
        p = inverse_lerp(u, v, t);
        p = inverse_sqrt(u);
        b = is_close(u, v);
        b = is_finite(u);
        b = is_inf(u);
        b = is_nan(u);
        b = is_pow2(j);
        b = is_small(v);
        p = ldexp(p, j);
        p = lerp(u, v, t);
        p = lerp(u, v, 0.6f);
        p = linear_step(0.1f, 0.8f, t);
        p = linear_step(u, v, t);
        p = log(t);
        i = log2(j);
        p = log2(t);
        p = log10(t);
        s = max(u);
        p = max(u, v);
        s = min(u);
        p = min(u, v);
        p = mirror(t);
        p = mirror(t, u, v);
        p = mirror(t, 0.1f, 0.5f);
        p = mix(u, v, t);
        p = mix(u, v, 0.6f);
        p = mod(u, v);
        p = mod(0.5f, v);
        p = mod(u, 0.5f);
        p = modf(u, &p);
        p = pointwise_multiply(u, v);
        p = pointwise_divide(u, v);
        p = pow(t, v);
        p = pow(t, j);
        p = pow(t, s);
        p = radians(u);
        p = repeat(t, u, v);
        p = repeat(t, 0.1f, 0.5f);
        p = round(t);
        p = round_even(t);
        p = saturate(t);
        p = sign(t);
        p = sin(t);
        p = sinh(t);
        p = smooth_step(0.1f, 0.8f, t);
        p = smooth_step(u, v, t);
        p = sqrt(t);
        p = step(u, t);
        p = step(0.2f, t);
        p = tan(t);
        p = tanh(t);
        p = trunc(t);
    }

    // to manually compare assembly
    {
        float const v_data[] = {1.0f, 2.0f, 3.0f};

        {
            float u_data[] = {v_data[0], v_data[1], v_data[2]};
            CHECK(u_data[0] == Approx(v_data[0]));
            CHECK(u_data[1] == Approx(v_data[1]));
            CHECK(u_data[2] == Approx(v_data[2]));

            u_data[0] += v_data[0];
            u_data[1] += v_data[1];
            u_data[2] += v_data[2];
            CHECK(u_data[0] == Approx(v_data[0] + v_data[0]));
            CHECK(u_data[1] == Approx(v_data[1] + v_data[1]));
            CHECK(u_data[2] == Approx(v_data[2] + v_data[2]));
        }

        {
            float const u_data[] = {0.8f, 0.6f, 0.0f};
            float const u_dot_v = u_data[0] * v_data[0] + u_data[1] * v_data[1] + u_data[2] * v_data[2];
            CHECK(u_dot_v == Approx(2.0f));
        }
    }
}
