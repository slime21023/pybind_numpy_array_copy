#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

py::array_t<double> copy_array(py::array_t<double> arr)
{
    // Get the shape and size of the original array
    py::buffer_info info = arr.request();
    size_t size = info.shape[0] * info.shape[1];

    // Create a new array of the same shape and copy the data
    py::array_t<double> new_arr({info.shape[0], info.shape[1]});
    std::memcpy(new_arr.mutable_data(), arr.data(), size * sizeof(double));

    return new_arr;
}

PYBIND11_MODULE(array_copy, m)
{
    m.def("copy_array", &copy_array, "Copy a NumPy array");
}
