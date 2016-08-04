
file(WRITE "${OUTPUT_FILE}" "")
foreach(INPUT_FILE ${INPUT_FILES})
  file(READ "${INPUT_FILE}" CONTENTS)
  file(APPEND "${OUTPUT_FILE}" "${CONTENTS}
")
endforeach(INPUT_FILE)
