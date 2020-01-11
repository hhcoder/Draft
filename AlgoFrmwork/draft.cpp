#include <iostream>
#include <array>
#include <queue>

class Cortex3A
{
};

namespace CrxUtil
{ 
    template <typename T, size_t I, size_t... J>
    struct MDArrayGeneral
    {
        using Nested = typename MDArrayGeneral<T, J...>::type;
        using type = std::array<Nested, I>;
    };

    template <typename T, size_t I>
    struct MDArrayGeneral<T, I>
    {
        using type = std::array<T,I>;
    };

    template <typename T, size_t I, size_t... J>
    struct MDArray : public MDArrayGeneral<T, I, J...>::type
    {
    };

    template <typename T>
    struct Point 
    {
        T x;
        T y;
    };
};

namespace Extern
{
    namespace QualcommMSM8250
    {
        using StatsHistogram = CrxUtil::MDArray<unsigned, 256, 4>;
        using StatsData = CrxUtil::MDArray<uint32_t, 64, 48, 4>;
        using StatsSaturateCount = CrxUtil::MDArray<unsigned, 64, 48, 4>;
        using BlockCount = unsigned;
        using AwbCalibData = unsigned;
    };
};

namespace Algo
{
    struct BrightnessCondition
    {
        static const int max_brightness = 1024;
        static const int min_brightness = 0;
        int curr_brightness_level;
    };

    struct ColorDistribution : std::vector<CrxUtil::Point<float>> 
    {
    };

    struct WhiteBalanceGain
    {
        float r_gain;
        float b_gain;
    };

};


namespace QualcommPlatform = Extern::QualcommMSM8250;

struct InternalResult
{
    int frame_id;

    struct RawInput
    {
        QualcommPlatform::StatsHistogram hist_data;
        QualcommPlatform::StatsData stats_data;
        QualcommPlatform::StatsSaturateCount saturate_cnt;
        QualcommPlatform::BlockCount block_count;
        QualcommPlatform::AwbCalibData calib_data;
    } raw_input;

    struct NormalizedInput 
    {
        CrxUtil::MDArray<unsigned, 128> y_hist;
    } normalized_input;

    struct MeteringResult
    {
        Algo::BrightnessCondition brightness_condition;
        Algo::ColorDistribution color_distribution;
    } metering_result;

    struct AdjustmentResult
    {
        Algo::WhiteBalanceGain rb_gain;
    } adjustment_result;
};

struct DataHistory : private std::queue<InternalResult>
{
};

class InputReader
{
    int Read(unsigned id, void* payload);
    int NotifyEOF();
};

// object which converts from raw input to normalized input
// the normalized input should be unified across different platform/stats
class InputNormalization
{
};

// object which converts points from normalized input to unified color space
class Metering 
{
};

// object which calculates how to adjust from data in unified color space
class Adjustment
{
};

// object which translate adjustment results to a normalized result
class ResultNormalization
{
};

class OuputWriter
{
    int Write(unsigned id, void* result);
};

int main(int argc, char* argv[])
{
    return 0;
}
