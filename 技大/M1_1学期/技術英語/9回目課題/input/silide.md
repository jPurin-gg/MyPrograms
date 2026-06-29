---
marp: true
theme: default
paginate: false
size: 16:9
style: |
  section {
    font-family: "Aptos", "Helvetica Neue", Arial, "Hiragino Sans", sans-serif;
    padding: 24px 38px;
    background: #f5f6f8;
    color: #1f2630;
  }

  h1 {
    margin: 0 0 4px;
    color: #101d42;
    font-size: 35px;
    line-height: 1.1;
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

# Vocabulary Learning Support System Using LLMs & Video Generation AI

<p class="subtitle">Learning English words through generated episodes and videos</p>

<div class="context">
  <div class="context-box">
    <div class="context-label">BACKGROUND</div>
    <div class="context-text">
      <ul>
        <li>Engineering students need vocabulary for papers, technical documents, and tests.</li>
        <li>Word-book learning is text-based and often separates words from usage scenes.</li>
        <li>Episodic memory suggests that scenes and experiences can support memorization.</li>
      </ul>
    </div>
  </div>
  <div class="context-box">
    <div class="context-label">PURPOSE</div>
    <div class="context-text">
      <ul>
        <li>Connect English words with concrete usage scenes.</li>
        <li>Use LLMs and video generation AI to create learning episodes automatically.</li>
        <li>Support vocabulary learning that is more memorable than word-book learning.</li>
      </ul>
    </div>
  </div>
</div>

<div class="layout">

<div>

<div class="flow">
  <div class="step">
    <div class="label">INPUT</div>
    <div class="step-title">Target<br>English Word</div>
    <div class="step-text">A learner enters the word to study.</div>
  </div>
  <div class="step">
    <div class="label">LLM 1</div>
    <div class="step-title">Example<br>Sentence</div>
    <div class="step-text">The LLM generates a natural sentence based on the word meaning.</div>
  </div>
  <div class="step">
    <div class="label">LLM 2</div>
    <div class="step-title">Video<br>Prompt</div>
    <div class="step-text">The sentence is converted into a scene description for video generation.</div>
  </div>
  <div class="step">
    <div class="label">VIDEO AI</div>
    <div class="step-title">Short<br>Video</div>
    <div class="step-text">Video generation AI visualizes the usage scene.</div>
  </div>
  <div class="step">
    <div class="label">LEARNER</div>
    <div class="step-title">Word + Sentence + Video</div>
    <div class="step-text">The learner connects the word with a memorable episode.</div>
  </div>
</div>

<p class="result">Goal: make vocabulary learning <strong>more memorable</strong> than word-book learning.</p>

</div>

<div class="side">
  <div class="panel">
    <h2>What the system shows</h2>
    <ul>
      <li>Target English word</li>
      <li>Meaning-based example sentence</li>
      <li>Short video of the usage scene</li>
    </ul>
  </div>
  <div class="panel">
    <h2>Current status</h2>
    <ul>
      <li>Basic system design is being organized</li>
      <li>Video generation has been tested with some words</li>
      <li>Concrete action words are easier to visualize</li>
      <li>Abstract words are still difficult to express</li>
    </ul>
  </div>
</div>

</div>

<!--
Speaker notes:

Hello, everyone. I will briefly explain the system I am studying.

The system supports English vocabulary learning by showing the usage scene of each word as a short video.

First, a learner inputs a target English word. Then, an LLM generates a natural example sentence based on the meaning of the word. Next, another LLM step converts the sentence into a prompt for video generation. Video generation AI uses the prompt to create a short video that shows the situation where the word is used.

The learner studies the word, the sentence, and the video together. The aim is to connect the word with a memorable episode, instead of memorizing it only as a translation.

At this stage, I have organized the basic design and tested video generation with some words. Concrete action words are relatively easy to visualize, but abstract words are still difficult. This is one of the main challenges of the system.
Thank you for listening.
-->
