import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { DriversModule } from './Drivers/drivers.module';
import { CircuitsModule } from './Circuits/circuits.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { PuppeteerService } from './ScrapeService/scrape.service';
import { GptService } from './gptService/gpt.service';
import { UsersModule } from './Users/users.module';

import { User } from './Entities/user.entity';
import { Driver } from './entities/driver.entity';

@Module({
  imports: [DriversModule,CircuitsModule,UsersModule,TypeOrmModule.forRoot({
    type: 'mysql',
  host: 'localhost',
  port: 3306,
  username: 'root',
  password: 'rHas9697!',
  database: 'f1db',
  entities: [User,Driver],
  synchronize: true,
  
})],
  controllers: [AppController],
  providers: [AppService,PuppeteerService,GptService],
})
export class AppModule {}



