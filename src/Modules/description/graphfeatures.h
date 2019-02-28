#ifndef GRAPHFEATURES_H
#define GRAPHFEATURES_H
/*
#include <map>
#include <opencv2/opencv.hpp>

template<typename _Df>
std::map<int, size_t> getLabel2RowDict(const _Df& dataframe, size_t rows, size_t labels_col)
{
    std::map<int, size_t> label2row;

    for(size_t row = 0; row < rows; ++row)
    {
        int label = int(dataframe[row][labels_col]);
        label2row[label] = row;
    }
}

class GraphFeatures
{
    enum GF{FIR_LABEL, SEC_LABEL, LINK_POWER};
    std::vector<cv::Vec3i> _graph_link_list;
public:
    GraphFeatures();
    GraphFeatures(const std::map<cv::Vec2i, int>& graph_link_list);
    void rebuild(const std::map<cv::Vec2i, int>& graph_link_list);

    template<typename _Df>
     average(const _Df& dataframe, size_t rows, size_t labels_col)
    {

        auto label2row = getLabel2RowDict<_Df>(dataframe, rows, labels_col);
        for(cv::Vec3i link: _graph_link_list)
        {
            size_t fir_row = label2row.at(link[GF::FIR_LABEL]);
            size_t sec_row = label2row.at(link[GF::SEC_LABEL]);

            double average =

        }
    }

    std::list<std::string> getHeader(const std::string& predicat="");
    std::list<double> getFeatures();


};*/

#endif // GRAPHFEATURES_H
