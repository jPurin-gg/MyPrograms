---
marp: true
theme: default
paginate: false
size: 16:9
style: |
  section {
    font-family: "Hiragino Sans", "Yu Gothic", "Aptos", "Helvetica Neue", Arial, sans-serif;
    padding: 24px 38px;
    background: #f5f6f8;
    color: #1f2630;
  }

  h1 {
    margin: 0 0 4px;
    color: #101d42;
    font-size: 34px;
    line-height: 1.15;
  }

  .subtitle {
    margin: 0 0 8px;
    color: #5d6678;
    font-size: 18px;
    font-weight: 700;
  }

  .context {
    display: grid;
    grid-template-columns: 1fr;
    gap: 7px;
    margin-bottom: 10px;
  }

  .context-box {
    padding: 7px 13px;
    background: #ffffff;
    border-left: 5px solid #00a6a0;
    box-shadow: 0 4px 12px rgba(16, 29, 66, 0.07);
  }

  .context-label {
    margin-bottom: 3px;
    color: #00a6a0;
    font-family: "SFMono-Regular", "Roboto Mono", monospace;
    font-size: 13px;
    font-weight: 900;
    letter-spacing: .08em;
  }

  .context-text {
    color: #1f2630;
    font-size: 15px;
    line-height: 1.32;
  }

  .context-text ul {
    margin: 0;
    padding-left: 17px;
  }

  .layout {
    display: grid;
    grid-template-columns: 1.45fr .86fr;
    gap: 14px;
    align-items: stretch;
  }

  .flow {
    display: grid;
    grid-template-columns: repeat(5, 1fr);
    gap: 9px;
  }

  .step {
    position: relative;
    min-height: 194px;
    padding: 12px 10px;
    border-top: 6px solid #00a6a0;
    background: #ffffff;
    box-shadow: 0 5px 14px rgba(16, 29, 66, 0.08);
  }

  .step:not(:last-child)::after {
    content: ">";
    position: absolute;
    top: 76px;
    right: -13px;
    z-index: 2;
    color: #00a6a0;
    font-size: 24px;
    font-weight: 900;
  }

  .label {
    color: #00a6a0;
    font-family: "SFMono-Regular", "Roboto Mono", monospace;
    font-size: 12px;
    font-weight: 900;
    letter-spacing: .08em;
  }

  .step-title {
    margin: 7px 0 8px;
    color: #101d42;
    font-size: 18px;
    font-weight: 900;
    line-height: 1.22;
  }

  .step-text {
    color: #1f2630;
    font-size: 14px;
    line-height: 1.4;
  }

  .side {
    display: grid;
    gap: 11px;
  }

  .panel {
    padding: 12px 14px;
    background: #fff;
    border-left: 5px solid #101d42;
    box-shadow: 0 5px 14px rgba(16, 29, 66, 0.08);
  }

  .panel h2 {
    margin: 0 0 6px;
    color: #101d42;
    font-size: 20px;
  }

  .panel ul {
    margin: 0;
    padding-left: 18px;
    font-size: 15px;
    line-height: 1.42;
  }

  li::marker {
    color: #00a6a0;
  }

  .result {
    margin-top: 11px;
    padding: 10px 14px;
    background: #101d42;
    color: #ffffff;
    font-size: 18px;
    font-weight: 700;
  }

  .result strong {
    color: #61d4cf;
  }
---

# 大規模言語モデルと動画生成AIを用いた英単語学習支援システム

<p class="subtitle">生成されたエピソードと動画を用いて英単語を学習する</p>

<div class="context">
  <div class="context-box">
    <div class="context-label">背景</div>
    <div class="context-text">
      <ul>
        <li>工学系学生には、論文・技術文書・試験のための英単語力が必要である。</li>
        <li>単語帳学習は文字中心で、単語が使用場面から切り離されやすい。</li>
        <li>エピソード記憶では、場面や経験と結びついた情報が記憶に残りやすい。</li>
      </ul>
    </div>
  </div>
  <div class="context-box">
    <div class="context-label">目的</div>
    <div class="context-text">
      <ul>
        <li>英単語を具体的な使用場面と結びつける。</li>
        <li>LLMと動画生成AIにより、学習用エピソードを自動生成する。</li>
        <li>単語帳よりも記憶に残る英単語学習を支援する。</li>
      </ul>
    </div>
  </div>
</div>

<div class="layout">

<div>

<div class="flow">
  <div class="step">
    <div class="label">INPUT</div>
    <div class="step-title">学習対象の<br>英単語</div>
    <div class="step-text">学習者が覚えたい単語を入力する。</div>
  </div>
  <div class="step">
    <div class="label">LLM 1</div>
    <div class="step-title">例文生成</div>
    <div class="step-text">単語の意味に合う自然な例文を生成する。</div>
  </div>
  <div class="step">
    <div class="label">LLM 2</div>
    <div class="step-title">動画プロンプト<br>作成</div>
    <div class="step-text">例文を動画生成向けの場面説明に変換する。</div>
  </div>
  <div class="step">
    <div class="label">VIDEO AI</div>
    <div class="step-title">短い動画を<br>生成</div>
    <div class="step-text">単語の使用場面を動画として可視化する。</div>
  </div>
  <div class="step">
    <div class="label">LEARNER</div>
    <div class="step-title">単語 + 例文 + 動画で学習</div>
    <div class="step-text">単語を記憶に残るエピソードと結びつける。</div>
  </div>
</div>

<p class="result">目標: 単語帳学習よりも<strong>記憶に残る</strong>英単語学習を実現する。</p>

</div>

<div class="side">
  <div class="panel">
    <h2>提示するもの</h2>
    <ul>
      <li>学習対象の英単語</li>
      <li>意味に沿った例文</li>
      <li>使用場面を表す短い動画</li>
    </ul>
  </div>
  <div class="panel">
    <h2>現在の状況</h2>
    <ul>
      <li>基本方針を整理</li>
      <li>一部単語で動画生成を試行</li>
      <li>具体的な動作語は映像化しやすい</li>
      <li>抽象語の表現方法が課題</li>
    </ul>
  </div>
</div>

</div>

<!--
発表メモ:

本研究では、大規模言語モデルと動画生成AIを用いた英単語学習支援システムについて説明します。

背景として、工学系学生には英単語力が必要ですが、単語帳だけでは単語が文脈から切り離され、記憶に残りにくいという課題があります。

そこで本研究では、単語を使用場面やエピソード記憶と結びつけることで、英単語学習を支援することを目的としています。

システムでは、まず学習者が覚えたい英単語を入力します。次に、LLMがその単語の意味に合う自然な例文を生成します。さらに、その例文をもとに、動画生成AIに入力するためのプロンプトを作成します。動画生成AIは、そのプロンプトから単語の使用場面を表す短い動画を生成します。

学習者は、単語、例文、動画を組み合わせて学習します。単語を単なる日本語訳として覚えるのではなく、場面やエピソードと結びつけて記憶することを狙っています。

現在は、基本方針の整理と一部単語での動画生成を試行しています。具体的な動作を表す単語は映像化しやすい一方で、抽象的な単語をどのように表現するかが課題です。
-->
