#include "decisiontree.h"

void DecisionTree::setDefault()
{
    _clf->setCVFolds(10);
    _clf->setMaxCategories(2);
    _clf->setMinSampleCount(10);
    _clf->setTruncatePrunedTree(true);
    _clf->setUse1SERule(true);
    _clf->setUseSurrogates(false);
    float _priors[] = { 1.0, 10.0 };
    cv::Mat priors( 1, 2, CV_32F, _priors );
    _clf->setPriors(priors);

}

void DecisionTree::fit(const Mat1f &samples, const Mat1f &answers_column)
{
    Mat responses(answers_column.rows,1,CV_32S);
    answers_column.convertTo(responses,CV_32S);
    auto data = TrainData::create(samples,ROW_SAMPLE,answers_column);
    data->setTrainTestSplitRatio(1.,false);
    setDefault();
    _clf->train(data);
    _is_valid = true;
}
