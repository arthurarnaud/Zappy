function DrawAll(startX, startY) {

    /* Draw Resources */
    for (var y = startY; y < startY + 10 && y < raw_map_resources.length; ++y) {

        for (var x = startX; x < startX + 10 && x < raw_map_resources[y].length; ++x) {

            var cell = raw_map_resources[y][x];

            DrawCellResources(cell, x, y);

        }

    }

    /* Draw Mobs */
    for (var i = 0; i < raw_mobs_list.length; ++i) {
        DrawCellMob(raw_mobs_list[i]);
    }

    /* Draw Eggs */
    for (var i = 0; i < raw_eggs_list.length; ++i) {
        DrawCellEgg(raw_eggs_list[i]);
    }

}

function DrawCellResources(cell_res, x, y) {

    if (cell_res.food > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.FOOD.X,
            y * 100 + SPRITES_POSITION.FOOD.Y, 'food');

        ScaleImage(
            image,
            SPRITES_POSITION.FOOD.SW,
            SPRITES_POSITION.FOOD.SH
        );

    }

    if (cell_res.linemate > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.LINEMATE.X,
            y * 100 + SPRITES_POSITION.LINEMATE.Y, 'linemate');

        ScaleImage(
            image,
            SPRITES_POSITION.LINEMATE.SW,
            SPRITES_POSITION.LINEMATE.SH
        );

    }

    if (cell_res.deraumere > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.DERAUMERE.X,
            y * 100 + SPRITES_POSITION.DERAUMERE.Y, 'deraumere');

        ScaleImage(
            image,
            SPRITES_POSITION.DERAUMERE.SW,
            SPRITES_POSITION.DERAUMERE.SH
        );

    }

    if (cell_res.sibur > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.SIBUR.X,
            y * 100 + SPRITES_POSITION.SIBUR.Y, 'sibur');

        ScaleImage(
            image,
            SPRITES_POSITION.SIBUR.SW,
            SPRITES_POSITION.SIBUR.SH
        );

    }

    if (cell_res.mendiane > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.MENDIANE.X,
            y * 100 + SPRITES_POSITION.MENDIANE.Y, 'mendiane');

        ScaleImage(
            image,
            SPRITES_POSITION.MENDIANE.SW,
            SPRITES_POSITION.MENDIANE.SH
        );

    }

    if (cell_res.phiras > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.PHIRAS.X,
            y * 100 + SPRITES_POSITION.PHIRAS.Y, 'phiras');

        ScaleImage(
            image,
            SPRITES_POSITION.PHIRAS.SW,
            SPRITES_POSITION.PHIRAS.SH
        );

    }

    if (cell_res.thystame > 0) {

        var image = resources_layer.create(
            x * 100 + SPRITES_POSITION.THYSTAME.X,
            y * 100 + SPRITES_POSITION.THYSTAME.Y, 'thystame');

        ScaleImage(
            image,
            SPRITES_POSITION.THYSTAME.SW,
            SPRITES_POSITION.THYSTAME.SH
        );

    }

}

function DrawCellMob(mob, x, y) {

    var image = resources_layer.create(
        mob.pos_x * 100 + SPRITES_POSITION.MOB.X,
        mob.pos_y * 100 + SPRITES_POSITION.MOB.Y, MOBS_COLOR[mob.teamId % MOBS_COLOR.length]);

    ScaleImage(
        image,
        SPRITES_POSITION.MOB.SW,
        SPRITES_POSITION.MOB.SH
    );

}

function DrawCellEgg(egg, x, y) {

    var image = resources_layer.create(
        egg.pos_x * 100 + SPRITES_POSITION.EGG.X,
        egg.pos_y * 100 + SPRITES_POSITION.EGG.Y, 'egg');

    ScaleImage(
        image,
        SPRITES_POSITION.EGG.SW,
        SPRITES_POSITION.EGG.SH
    );

}