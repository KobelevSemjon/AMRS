#include "logisticregressor.h"

void LogisticRegressor::setDefault()
{
    _clf->setTrainMethod(LogisticRegression::Methods::BATCH);
}

void LogisticRegressor::setIterations(int val)
{
    _clf->setIterations(val);
}

void LogisticRegressor::setLearningRate(double val)
{
    _clf->setLearningRate(val);
}

void LogisticRegressor::setRegularization(int val)
{
    _clf->setRegularization(val);
}

int LogisticRegressor::getIterations()
{
    return _clf->getIterations();
}

double LogisticRegressor::getLearningRate()
{
    return _clf->getLearningRate();
}

int LogisticRegressor::getRegularization()
{
    return _clf->getRegularization();
}

string LogisticRegressor::getParams()
{
    std::stringstream ss;
    ss << "{";
    ss << "LearningRate = " << getLearningRate() << ";\n";
    ss << "Iterations = " << getIterations() << ";\n";
    ss << "Regularization = ";
    switch (getRegularization()) {
    case -1: ss << "REG_DISABLE"; break;
    case 0: ss << "REG_L1"; break;
    case 1: ss << "L2"; break;
    default: ss << "UNKNOWN";
    }
    ss << "}";
    return ss.str();
}
