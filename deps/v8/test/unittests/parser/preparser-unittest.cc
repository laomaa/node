// Copyright 2017 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/api/api-inl.h"
#include "src/objects/objects-inl.h"
#include "test/unittests/test-helpers.h"
#include "test/unittests/test-utils.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace v8 {
namespace internal {

class PreParserTest : public TestWithNativeContext {
 public:
  PreParserTest() = default;
  PreParserTest(const PreParserTest&) = delete;
  PreParserTest& operator=(const PreParserTest&) = delete;
};

TEST_F(PreParserTest, LazyFunctionLength) {
  const char* script_source = "function lazy(a, b, c) { } lazy";

  Handle<JSFunction> lazy_function = RunJS<JSFunction>(script_source);

  Handle<SharedFunctionInfo> shared(lazy_function->shared(),
                                    lazy_function->GetIsolate());
  CHECK_EQ(3, shared->length());

  Handle<Smi> length = RunJS<Smi>("lazy.length");
  int32_t value;
  CHECK(length->ToInt32(&value));
  CHECK_EQ(3, value);
}

}  // namespace internal
}  // namespace v8
