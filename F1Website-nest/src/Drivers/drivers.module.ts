import { Module } from '@nestjs/common';
import { DriversController } from './drivers.controller';
import { DriversService } from './drivers.service';
// import { PuppeteerService } from 'src/ScrapeService/scrape.service';
import { GptService } from 'src/gptService/gpt.service';
import { Driver } from 'src/entities/driver.entity';
import { TypeOrmModule } from "@nestjs/typeorm";



@Module({
    imports: [TypeOrmModule.forFeature([Driver])],
    controllers: [DriversController],
    providers: [DriversService,GptService]
})
export class DriversModule {}