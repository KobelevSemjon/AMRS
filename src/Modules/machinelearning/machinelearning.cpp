#include "machinelearning.h"

Mat shuffleRows(const Mat &matrix, int seed)
{
    std::vector <int> seeds;
    seeds.reserve(size_t(matrix.rows));
    for (int cont = 0; cont < matrix.rows; cont++)
        seeds.push_back(cont);

    shuffle(begin(seeds), end(seeds), mt19937(seed));

    cv::Mat output;
    output.reserve(size_t(matrix.rows));
    for (int cont = 0; cont < matrix.rows; cont++)
        output.push_back(matrix.row(seeds[size_t(cont)]));

    return output;
}


std::pair<Mat1f, Mat1f> random_split(Mat1f matrix, double size, int seed)
{
    if(size<0.) return std::make_pair(matrix, Mat1f());
    if(size>1.) return std::make_pair(Mat1f(), matrix);

    std::vector <int> seeds;
    seeds.reserve(size_t(matrix.rows));
    for (int cont = 0; cont < matrix.rows; cont++)
        seeds.push_back(cont);

    shuffle(begin(seeds), end(seeds), mt19937(seed));

    size_t train_size = size_t(matrix.rows*(1-size));

    Mat1f train;
    train.reserve(train_size);
    size_t i = 0;
    for (; i < train_size; ++i)
        train.push_back(matrix.row(seeds[i]));

    Mat1f test;
    test.reserve(size_t(matrix.rows) - train_size);
    for (; i < size_t(matrix.rows); ++i)
        test.push_back(matrix.row(seeds[i]));

    return std::make_pair(train,test);
}
std::tuple<Mat1f,Mat1f,Mat1f,Mat1f> train_test_split(const Mat1f& X, const Mat1f& y, double size, int seed)
{
    if(X.rows!=y.rows) throw std::invalid_argument("train_test_split: X.rows and y.rows must be equal");

    //enum{TrainPos,TrainNeg,TestPos,TestNeg};

    vector<int> PosPositions;
    vector<int> NegPositions;
    for(int row=0; row<y.rows; ++row)
    {
        if (y(row,0)>0.5f) PosPositions.push_back(row);
        else NegPositions.push_back(row);
    }
    //cout<<"1:"<<PosPositions.size()<<"+ "<<NegPositions.size()<<"-\n";

    shuffle(begin(PosPositions), end(PosPositions), mt19937(seed));
    int pos_test_size = int(size*PosPositions.size());
    vector<int> PosTestPositions;
    vector<int> PosTrainPositions;
    int k = 0;
    for(int pos: PosPositions)
    {
        if(k<pos_test_size) PosTestPositions.push_back(pos);
        else PosTrainPositions.push_back(pos);
        ++k;
    }
    //cout<<"2:"<<pos_test_size << "==" << PosTestPositions.size();
    shuffle(begin(NegPositions), end(NegPositions), mt19937(seed));
    int neg_test_size = int(size*NegPositions.size());
    vector<int> NegTestPositions;
    vector<int> NegTrainPositions;
    int j = 0;
    for(int pos: NegPositions)
    {
        if(j<neg_test_size) NegTestPositions.push_back(pos);
        else NegTrainPositions.push_back(pos);
        ++j;
    }
    //cout<<"\n3:"<<neg_test_size << "==" << NegTestPositions.size();

    vector<int> TestPositions(PosTestPositions);
    copy(begin(NegTestPositions),end(NegTestPositions),back_inserter(TestPositions));

    shuffle(begin(TestPositions), end(TestPositions), mt19937(seed));
    size_t test_size = TestPositions.size();
    Mat1f y_test; y_test.reserve(test_size);
    Mat1f X_test; X_test.reserve(test_size);
    for(int pos: TestPositions)
    {
        y_test.push_back(y.row(pos));
        X_test.push_back(X.row(pos));
    }

    //cout<<"\n4:"<<test_size << "==" << TestPositions.size();
    vector<int> TrainPositions(PosTrainPositions);
    copy(begin(NegTrainPositions),end(NegTrainPositions),back_inserter(TrainPositions));

    shuffle(begin(TrainPositions), end(TrainPositions), mt19937(seed));
    size_t train_size = size_t(size_t(y.rows) - test_size);
    Mat1f y_train; y_train.reserve(train_size);
    Mat1f X_train; X_train.reserve(train_size);
    for(int pos: TrainPositions)
    {
        y_train.push_back(y.row(pos));
        X_train.push_back(X.row(pos));
    }
    //cout<<"\n5:"<<train_size << "==" <<TrainPositions.size();
    //auto X_train_test = random_split(X,size,seed);
    //auto y_train_test = random_split(y,size,seed);
    //auto& X_train = X_train_test.first;
    //auto& y_train = y_train_test.first;
    //auto& X_test = X_train_test.second;
    //auto& y_test = y_train_test.second;;
    return make_tuple(X_train, y_train, X_test, y_test);
}

std::pair<int, int> getPosAndNegCount(const Mat1f &y, float th)
{
    int posCount = 0, negCount = 0;
    for(int row = 0; row < y.rows; ++row)
    {
        if (y(row,0) > th) ++negCount;
        else ++posCount;
    }
    return make_pair(posCount, negCount);
}
