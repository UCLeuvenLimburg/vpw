(let [[size & input] (line-seq (java.io.BufferedReader. *in*))]
  (doseq [line input]
    (let [[index word] (clojure.string/split line #" ")]
     (println (nth word (dec (Integer/parseInt index)))))))