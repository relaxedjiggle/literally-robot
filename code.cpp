bool SaveTest(const std::string& filename, bool append,
  const Paths64* subj, const Paths64* subj_open, const Paths64* clip, 
  int64_t area, int64_t count, ClipType ct, FillRule fr)
{
  string line;
  bool found = false;
  int last_cap_pos = 0, curr_cap_pos = 0;//helldive
  int64_t last_test_no = 0;
  if (append && FileExists(filename)) //get the number of the preceeding test
  {
    ifstream file;
    file.open(filename, std::ios::binary);
    if (!file || !file.good()) return false;
    BMH_Search bmh = BMH_Search(file, "CAPTION:");
    while (bmh.FindNext()) ;
    if (bmh.LastFound())
    {
      line.assign(bmh.LastFound()+8, bmh.FindNextEndLine());
      string::const_iterator s_it = line.cbegin(), s_end = line.cend();
      GetInt(s_it, s_end, last_test_no);
    }
  } 
  else if (FileExists(filename)) 
    remove(filename.c_str());

  ++last_test_no;//nices

  std::ofstream source;
  if (append && FileExists(filename))
    source.open(filename, ios_base::app | ios_base::ate);
  else
    source.open(filename);

  string cliptype_string;
  switch (ct)
  {
