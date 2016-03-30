//===----------------------------------------------------------------------===//
//
//                         PelotonDB
//
// configuration.cpp
//
// Identification: benchmark/ycsb/configuration.cpp
//
// Copyright (c) 2015, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "backend/benchmark/ycsb/ycsb_configuration.h"

#include <iomanip>
#include <algorithm>


namespace peloton {
namespace benchmark {
namespace ycsb {

void Usage(FILE *out) {
  fprintf(out,
          "Command line options : ycsb <options> \n"
          "   -h --help              :  Print help message \n"
          "   -k --scale-factor      :  # of tuples \n"
          "   -t --transactions      :  # of transactions \n"
          "   -c --column_count      :  # of columns \n"
          "   -u --write_ratio       :  Fraction of updates \n"
          "   -b --backend_count     :  # of backends \n");
  exit(EXIT_FAILURE);
}

static struct option opts[] = {
    {"scale-factor", optional_argument, NULL, 'k'},
    {"transactions", optional_argument, NULL, 't'},
    {"column_count", optional_argument, NULL, 'c'},
    {"update_ratio", optional_argument, NULL, 'u'},
    {"backend_count", optional_argument, NULL, 'b'},
    {NULL, 0, NULL, 0}};

void ValidateScaleFactor(const configuration &state) {
  if (state.scale_factor <= 0) {
    std::cout << "Invalid scalefactor :: " << state.scale_factor << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setw(20) << std::left << "scale_factor "
      << " : " << state.scale_factor << std::endl;
}

void ValidateColumnCount(const configuration &state) {
  if (state.column_count <= 0) {
    std::cout << "Invalid column_count :: " << state.column_count
        << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setw(20) << std::left << "column_count "
      << " : " << state.column_count << std::endl;
}

void ValidateUpdateRatio(const configuration &state) {
  if (state.update_ratio < 0 || state.update_ratio > 1) {
    std::cout << "Invalid update_ratio :: " << state.update_ratio << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setw(20) << std::left << "update_ratio "
      << " : " << state.update_ratio << std::endl;
}

void ValidateBackendCount(const configuration &state) {
  if (state.backend_count <= 0) {
    std::cout << "Invalid backend_count :: " << state.backend_count
        << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setw(20) << std::left << "backend_count "
      << " : " << state.backend_count << std::endl;
}

void ValidateTransactionCount(const configuration &state) {
  if (state.transaction_count <= 0) {
    std::cout << "Invalid transaction_count :: " << state.transaction_count
        << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setw(20) << std::left << "transaction_count "
      << " : " << state.transaction_count << std::endl;
}

int orig_scale_factor;

void ParseArguments(int argc, char *argv[], configuration &state) {

  // Default Values
  state.scale_factor = 1;
  state.transaction_count = 10000;
  state.column_count = 10;
  state.update_ratio = 0.5;
  state.backend_count = 2;

  // Parse args
  while (1) {
    int idx = 0;
    int c = getopt_long(argc, argv, "ahk:t:c:u:b:", opts, &idx);

    if (c == -1) break;

    switch (c) {
      case 'k':
        state.scale_factor = atoi(optarg);
        break;
      case 't':
        state.transaction_count = atoi(optarg);
        break;
      case 'c':
        state.column_count = atoi(optarg);
        break;
      case 'u':
        state.update_ratio = atof(optarg);
        break;
      case 'b':
        state.backend_count = atoi(optarg);
        break;
      case 'h':
        Usage(stderr);
        break;

      default:
        fprintf(stderr, "\nUnknown option: -%c-\n", c);
        Usage(stderr);
    }
  }

  // Print configuration
  ValidateScaleFactor(state);
  ValidateColumnCount(state);
  ValidateUpdateRatio(state);
  ValidateBackendCount(state);
  ValidateTransactionCount(state);

}

}  // namespace ycsb
}  // namespace benchmark
}  // namespace peloton
