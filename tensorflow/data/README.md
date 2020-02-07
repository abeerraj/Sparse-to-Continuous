# Datasets Info

## Number of Available Images/Depths for each dataset
# TODO: Provavelmente após eu atualizar os Splits do KITTI Continuous e KITTI Discrete, esta tabela não está mais correta!
| Dataset                       | Train  | Test  |
| ----------------------------- | -----: | ----: |
| apolloscape                   | 102686 | 25672 |
| nyudepth                      |    795 |   654 |
| kitti_depth                   |  85898 |  6852 |*
| ----------------------------- | ------ | ----- |
| kitti_continuous              |  25742 |  6436 |
| kitti_continuous_city         |   6618 |  1655 |
| kitti_continuous_residential  |  10529 |  2633 |
| kitti_continuous_road         |   4188 |  1048 |
| kitti_continuous_campus       |    999 |   250 |
| kitti_continuous_person       |   3406 |   852 |
| ----------------------------- | ------ | ----- |
| kitti_discrete                |  25742 |  6436 |
| kitti_discrete_city           |   6618 |  1655 |
| kitti_discrete_residential    |  10529 |  2633 |
| kitti_discrete_road           |   4188 |  1048 |
| kitti_discrete_campus         |    999 |   250 |
| kitti_discrete_person         |   3406 |   852 |

* Validation Subset used instead of Test Subset. The Test Subset doesn't have ground truth images.