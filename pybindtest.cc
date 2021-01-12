#include <iostream>
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/writer.h>
#include <pybind11/pybind11.h>

std::shared_ptr<arrow::Table> generate_table() {
  arrow::Int64Builder i64builder;
  std::shared_ptr<arrow::Array> i64array;
  PARQUET_THROW_NOT_OK(i64builder.AppendValues({2, 4}));
  PARQUET_THROW_NOT_OK(i64builder.Finish(&i64array));

  arrow::StringBuilder strbuilder;
  std::shared_ptr<arrow::Array> strarray;
  PARQUET_THROW_NOT_OK(strbuilder.Append("some"));
  PARQUET_THROW_NOT_OK(strbuilder.Append("content"));
  PARQUET_THROW_NOT_OK(strbuilder.Finish(&strarray));

  std::shared_ptr<arrow::Schema> schema = arrow::schema(
      {arrow::field("int", arrow::int64()), 
       arrow::field("str", arrow::utf8())});

  return arrow::Table::Make(schema, {i64array, strarray});
}

void write_parquet_file(const arrow::Table& table) {
  std::shared_ptr<arrow::io::FileOutputStream> outfile;
  PARQUET_ASSIGN_OR_THROW(outfile,arrow::io::FileOutputStream::Open("pybindtest.parquet"));
  PARQUET_THROW_NOT_OK(parquet::arrow::WriteTable(table, arrow::default_memory_pool(), outfile, 3));
}

void python_bind_test() {
  std::shared_ptr<arrow::Table> table = generate_table();
  write_parquet_file(*table);
}

PYBIND11_MODULE(pybindtest, m) {
  m.def("python_bind_test", &python_bind_test);
}
