# 使い方:
# Rscript valo.R valo.csv valo_result

args <- commandArgs(trailingOnly = TRUE)

if (length(args) < 2) {
  stop("使い方: Rscript valo.R 入力CSVファイル名 出力ファイル名の接頭辞")
}

input_file <- args[1]
output_prefix <- args[2]

# CSVと同じフォルダに出力する
output_dir <- dirname(input_file)
if (output_dir == ".") {
  output_dir <- getwd()
}

summary_file  <- file.path(output_dir, paste0(output_prefix, "_summary.txt"))
scores_file   <- file.path(output_dir, paste0(output_prefix, "_scores.csv"))
loadings_file <- file.path(output_dir, paste0(output_prefix, "_loadings.csv"))
plot_file     <- file.path(output_dir, paste0(output_prefix, "_plot.png"))

# CSV読み込み
df <- read.csv(input_file, row.names = 1, check.names = FALSE, fileEncoding = "UTF-8")

# 数値列だけを使用
numeric_data <- df[, sapply(df, is.numeric), drop = FALSE]

if (ncol(numeric_data) < 2) {
  stop("PCAには数値列が2列以上必要です。")
}

# 主成分分析
result <- prcomp(numeric_data, scale. = TRUE)

# 固有値・寄与率・累積寄与率を日本語で作成
eigenvalues <- result$sdev^2
contribution <- eigenvalues / sum(eigenvalues)
cumulative_contribution <- cumsum(contribution)

contribution_df <- data.frame(
  主成分 = paste0("第", seq_along(eigenvalues), "主成分"),
  固有値 = round(eigenvalues, 4),
  寄与率 = round(contribution, 4),
  寄与率パーセント = paste0(round(contribution * 100, 2), "%"),
  累積寄与率 = round(cumulative_contribution, 4),
  累積寄与率パーセント = paste0(round(cumulative_contribution * 100, 2), "%")
)

# 主成分得点
scores <- as.data.frame(result$x)
colnames(scores) <- paste0("第", seq_len(ncol(scores)), "主成分")

# 主成分係数
loadings <- as.data.frame(result$rotation)
colnames(loadings) <- paste0("第", seq_len(ncol(loadings)), "主成分")

# 結果をテキスト出力
sink(summary_file)

cat("=== 主成分分析の結果 ===\n\n")

cat("【入力ファイル】\n")
cat(input_file, "\n\n")

cat("【使用した数値データ】\n")
print(numeric_data)

cat("\n【固有値・寄与率・累積寄与率】\n")
print(contribution_df, row.names = FALSE)

cat("\n【主成分得点】\n")
print(round(scores, 4))

cat("\n【主成分係数】\n")
print(round(loadings, 4))

cat("\n【解釈の目安】\n")
cat("・寄与率は，各主成分がデータ全体の情報をどれだけ説明しているかを表す。\n")
cat("・累積寄与率は，第1主成分から順にどれだけ情報を説明できているかを表す。\n")
cat("・主成分得点は，各データが主成分軸上でどの位置にあるかを表す。\n")
cat("・主成分係数は，各特徴量が主成分にどの程度影響しているかを表す。\n")

sink()

# CSV出力
write.csv(scores, scores_file, fileEncoding = "UTF-8")
write.csv(loadings, loadings_file, fileEncoding = "UTF-8")

# 日本語フォント指定（Mac向け）
jp_font <- "Hiragino Sans"

# PC1-PC2散布図を画像出力
png(plot_file, width = 800, height = 800)

par(family = jp_font)

plot(
  scores[[1]],
  scores[[2]],
  xlab = "第1主成分",
  ylab = "第2主成分",
  main = "主成分分析の結果",
  pch = 16
)

text(
  scores[[1]],
  scores[[2]],
  labels = rownames(scores),
  pos = 3,
  cex = 0.8,
  family = jp_font
)

grid()
dev.off()

cat("PCAが完了しました。\n")
cat("出力ファイル:\n")
cat(summary_file, "\n")
cat(scores_file, "\n")
cat(loadings_file, "\n")
cat(plot_file, "\n")