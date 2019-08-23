#ifndef EASYPR_TRAIN_SVMTRAIN_H_
#define EASYPR_TRAIN_SVMTRAIN_H_

#include "/home/pi/RoboTurtle/Turtle/easypr/train/train.h"
#include <vector>
#include "/home/pi/RoboTurtle/Turtle/easypr/config.h"
#include "/home/pi/RoboTurtle/Turtle/easypr/core/feature.h"

namespace easypr {

//int svmTrain(bool dividePrepared, bool trainPrepared);

class SvmTrain : public ITrain {
 public:
  typedef struct {
    std::string file;
    SvmLabel label;
  } TrainItem;

  SvmTrain(const char* plates_folder, const char* xml);

  virtual void train();

  virtual void test();

 private:
  void prepare();

  virtual cv::Ptr<cv::ml::TrainData> tdata();

  cv::Ptr<cv::ml::SVM> svm_;
  const char* plates_folder_;
  const char* svm_xml_;
  std::vector<TrainItem> train_file_list_;
  std::vector<TrainItem> test_file_list_;

  svmCallback extractFeature;
  bool isPrepared = true;
};
}

#endif  // EASYPR_TRAIN_SVMTRAIN_H_
