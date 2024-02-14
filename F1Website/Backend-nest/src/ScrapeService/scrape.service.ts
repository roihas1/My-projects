import { Injectable } from '@nestjs/common';
import puppeteer from 'puppeteer';

@Injectable()
export class PuppeteerService {
    async runPuppeteer(url:string) {
        const browser = await puppeteer.launch(
            {headless: false,}
        );
        const page = await browser.newPage();
    
        await page.goto(url, {waitUntil: 'domcontentloaded'}  );
        console.log("from scrape "+url);
        await page.waitForSelector('#mw-content-text > div.mw-parser-output > p:first-of-type');
        const p = await page.$eval('#mw-content-text > div.mw-parser-output > p:first-of-type', el => el.textContent);
        // Your Puppeteer code here       
        await browser.close();
        console.log("from scrape"+p);
        return p;
      
    }
  }


