class TypingTest {
    constructor() {
        this.init();
        this.bindEvents();
    }

    init() {
        // DOM elements
        this.textDisplay = document.getElementById('textDisplay');
        this.wpmDisplay = document.getElementById('wpm');
        this.accuracyDisplay = document.getElementById('accuracy');
        this.timerDisplay = document.getElementById('timer');
        this.resultOverlay = document.getElementById('result');
        this.finalWpm = document.getElementById('finalWpm');
        this.finalAccuracy = document.getElementById('finalAccuracy');
        this.personalBest = document.getElementById('personalBest');
        this.retryBtn = document.getElementById('retryBtn');
        
        // State variables
        this.timeLeft = 30;
        this.isTyping = false;
        this.timerInterval = null;
        this.currentIndex = 0;
        this.errors = 0;
        this.totalCharacters = 0;

        // Add text samples for different modes
        this.textSamples = {
            time: [
                "the quick brown fox jumps over the lazy dog",
                "to be or not to be that is the question",
                "all that glitters is not gold",
                "practice makes perfect keep trying",
                "success is not final failure is not fatal"
            ],
            punctuation: [
                "Hello, World! How are you today?",
                "Stop! Wait... Are you sure about this?",
                "The user said: \"This is amazing!\"",
                "Monday, Tuesday, Wednesday; then comes Thursday.",
                "What's the meaning of life? That's a good question!"
            ],
            numbers: [
                "In 2024, there are 366 days to remember.",
                "The room number is 404, not 405.",
                "Call 555-0123 for customer support.",
                "Chapter 7, Section 3.14 covers everything.",
                "100% of the time, it works every time!"
            ]
        };

        this.currentMode = 'time';
        this.reset();
    }

    bindEvents() {
        // Time button handlers
        document.querySelectorAll('.time-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                document.querySelector('.time-btn.active').classList.remove('active');
                e.target.classList.add('active');
                this.timeLeft = parseInt(e.target.dataset.time);
                this.reset();
            });
        });

        // Reset and retry button handlers
        document.getElementById('resetBtn').addEventListener('click', () => this.reset());
        this.retryBtn.addEventListener('click', () => this.reset());
        
        // Keyboard input handler
        document.addEventListener('keydown', (e) => {
            // Ignore if test is finished
            if (this.timeLeft <= 0) return;
            
            // Handle special keys
            if (e.key === 'Tab') {
                e.preventDefault();
                this.reset();
                return;
            }
            
            // Ignore modifier keys and function keys
            if (e.key.length > 1 || e.ctrlKey || e.altKey || e.metaKey) return;
            
            // Prevent default behavior for typing
            e.preventDefault();
            
            // Start the test on first keypress
            if (!this.isTyping) {
                this.startTest();
            }
            
            this.handleKeypress(e.key);
        });

        // Mode selection handlers
        document.querySelectorAll('.mode-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                document.querySelector('.mode-btn.active').classList.remove('active');
                e.target.classList.add('active');
                this.currentMode = e.target.dataset.mode;
                this.reset();
            });
        });
    }

    startTest() {
        this.isTyping = true;
        document.querySelector('.focus-info').style.display = 'none';
        this.startTimer();
    }

    reset() {
        clearInterval(this.timerInterval);
        this.isTyping = false;
        this.currentIndex = 0;
        this.errors = 0;
        this.totalCharacters = 0;
        this.timeLeft = parseInt(document.querySelector('.time-btn.active').dataset.time);
        this.timerDisplay.textContent = this.timeLeft;
        this.currentText = this.getRandomText();
        this.renderText();
        this.updateDisplay();
        this.resultOverlay.style.display = 'none';
        document.querySelector('.focus-info').style.display = 'block';
    }

    getRandomText() {
        const texts = this.textSamples[this.currentMode];
        return texts[Math.floor(Math.random() * texts.length)];
    }

    renderText() {
        let html = '';
        for (let i = 0; i < this.currentText.length; i++) {
            if (i === this.currentIndex) {
                html += `<span class="current">${this.currentText[i]}</span>`;
            } else if (i < this.currentIndex) {
                html += `<span class="correct">${this.currentText[i]}</span>`;
            } else {
                html += `<span>${this.currentText[i]}</span>`;
            }
        }
        this.textDisplay.innerHTML = html;
    }

    startTimer() {
        this.timerInterval = setInterval(() => {
            this.timeLeft--;
            this.timerDisplay.textContent = this.timeLeft;
            
            if (this.timeLeft <= 0) {
                this.finish();
            }
        }, 1000);
    }

    handleKeypress(key) {
        if (key === this.currentText[this.currentIndex]) {
            this.currentIndex++;
            this.totalCharacters++;
        } else {
            this.errors++;
            this.totalCharacters++;
        }

        if (this.currentIndex >= this.currentText.length) {
            this.currentText = this.getRandomText();
            this.currentIndex = 0;
        }

        this.renderText();
        this.updateDisplay();
    }

    calculateWPM() {
        const timeElapsed = (parseInt(document.querySelector('.time-btn.active').dataset.time) - this.timeLeft) / 60;
        const words = this.totalCharacters / 5; // Standard: 5 characters = 1 word
        return Math.round(words / timeElapsed) || 0;
    }

    calculateAccuracy() {
        if (this.totalCharacters === 0) return 100;
        return Math.round(((this.totalCharacters - this.errors) / this.totalCharacters) * 100);
    }

    updateDisplay() {
        this.wpmDisplay.textContent = this.calculateWPM();
        this.accuracyDisplay.textContent = this.calculateAccuracy();
    }

    finish() {
        clearInterval(this.timerInterval);
        const finalWPM = this.calculateWPM();
        const finalAccuracy = this.calculateAccuracy();

        // Update final stats
        this.finalWpm.textContent = finalWPM;
        this.finalAccuracy.textContent = finalAccuracy;

        // Update personal best
        const bestWPM = localStorage.getItem('bestWPM') || 0;
        if (finalWPM > bestWPM) {
            localStorage.setItem('bestWPM', finalWPM);
        }
        this.personalBest.querySelector('.pb-value').textContent = `${Math.max(finalWPM, bestWPM)} wpm`;

        // Show results
        this.resultOverlay.style.display = 'flex';
    }
}

// Initialize the typing test when the page loads
document.addEventListener('DOMContentLoaded', () => {
    new TypingTest();
}); 