const events = document.querySelectorAll(".tpg-shortcode-main-wrapper .rt-detail .entry-title a");
let regex = /(\d{4}\.\d{2}\.\d{2})/;

for (let i = 0; i < events.length; i++) {
    let text = events[i].innerHTML;
    let match = text.match(regex);
    
    if (match) {
        let date = match[1];
        text = text.replace(date, "");
        
        if (text.startsWith(" – ")) {
            text = text.slice(3);
        }
        
        date_tag = document.createElement("b");
        date_tag.innerText = date;
        
        text_tag = document.createElement("div");
        text_tag.innerText = text;
        text_tag.style.padding = "8px 0px 0px 0px";
        
        events[i].innerText = "";
        events[i].insertBefore(date_tag, undefined);
        events[i].insertBefore(text_tag, undefined);
    }
}


const pdfButtons = document.querySelectorAll("div.cta_wrapper > p > a > button");
for (let i = 0; i < pdfButtons.length; i++) {
    pdfButtons[i].innerHTML = "Otwórz na cały ekran";
    pdfButtons[i].className = "qbutton big_large_full_width icon_right";
}

