import {  Controller, Get, Inject, Query } from '@nestjs/common';
import { DriversService } from './drivers.service';
// import { PuppeteerService } from '../ScrapeService/scrape.service';

@Controller('drivers')
export class DriversController {
    @Inject(DriversService)
    private readonly driversService: DriversService;

    @Get("/driversByYear")
    async getDriversByYear(@Query('year') year: number) {
        const drivers = await this.driversService.getDriversByYear(year);
        return drivers;
    }
    @Get('/allDrivers')
    async getAllDrivers() {
        const drivers = await this.driversService.getAllDrivers();
        return drivers;
    }
    @Get('/randomDrivers')
    async getRandomDrivers() {
        const drivers = await this.driversService.getRandomDrivers();
        return drivers;
    }
    @Get('/searchDriver')
    async searchDriver(@Query('name') name: string) {
        const drivers = await this.driversService.searchDriver(name);
        if (drivers.length === 0){
            return "No driver found";
        }
        return drivers;
    }
    @Get('/driverStandingsByYear')
    async getStandingsByYear(@Query('year') year: number) {
        const standings = await this.driversService.getStandingsByYear(year);
        return standings;
    }

    @Get('/driverInfo')
    async getDriverInfo(@Query('driverId') driverId: string) {
        const driver = await this.driversService.getDriverPointsInfo(driverId);
        return driver;
    }

}
