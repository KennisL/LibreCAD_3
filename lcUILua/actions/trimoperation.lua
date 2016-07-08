TrimOperation = {}
TrimOperation.__index = TrimOperation

setmetatable(TrimOperation, {
    __index = Operations,
    __call = function (o, ...)
        local self = setmetatable({}, o)
        self:_init(...)
        return self
    end,
})

function TrimOperation:_init(id)
    Operations._init(self, id)

    self.limit = nil
    self.toTrim = nil
    self.intersectionPoints = {}
    self.toRemovePoint = nil

    event.register("point", self)
    event.register("selectionChanged", self)

    message("Select limit entity")
end

function TrimOperation:onEvent(eventName, ...)
    if(Operations.forMe(self) == false) then
        return
    end

    if(eventName == "selectionChanged") then
        self:selectionChanged()
    elseif(eventName == "point") then
        self:newPoint(...)
    end
end

function TrimOperation:selectionChanged()
    if(self.toTrim == nil) then
        nbEntities = #active_widget():selection()
        if(nbEntities == 1) then
            if(self.limit == nil) then
                self.limit = active_widget():selection()[1]

                message("Select entity to trim")
            elseif(self.toTrim == nil) then
                self.toTrim = active_widget():selection()[1]

                self:getIntersectionPoints()
            end
        elseif(nbEntities > 1) then
            message("Select only one entity")
        end
    end
end

function TrimOperation:newPoint(point)
    if(#self.intersectionPoints >= 1) then
        self.toRemovePoint = Operations:getCoordinate(point)

        self:trim()
    end
end

function TrimOperation:getIntersectionPoints()
    local intersect = IntersectMany({self.toTrim, self.limit})
    self.intersectionPoints = intersect:result()

    if(#self.intersectionPoints == 0) then
        message("No intersection found")

        self:close()
    elseif(#self.intersectionPoints >= 1) then
        message("Click on the part of the entity to remove")
    end
end

function TrimOperation:trim()
    local b = Builder(active_widget():document())
    b:append(self.toTrim)

    b:push()
    b:remove()
    b:processStack()

    if(self.toTrim.entityType == "line") then
        local point = self.toTrim:nearestPointOnEntity(self.toRemovePoint)
        local start = self.toTrim:start()
        local finish = self.toTrim:finish()

        local startToPoint = point:distanceTo(start)

        local previousIntersect = start
        local previousIntersectDistance = 0

        local nextIntersect = finish
        local nextIntersectDistance = start:distanceTo(finish)

        for k, v in pairs(self.intersectionPoints) do
            local startToIntersect = start:distanceTo(v)

            if(startToIntersect < startToPoint and startToIntersect > previousIntersectDistance) then
                previousIntersect = v
                previousIntersectDistance = startToIntersect
            elseif(startToIntersect > startToPoint and startToIntersect < nextIntersectDistance) then
                nextIntersect = v
                nextIntersectDistance = startToIntersect
            end
        end

        if(previousIntersect == start) then
            b:append(Line(nextIntersect, finish, self.toTrim:layer()))
        elseif(nextIntersect == finish) then
            b:append(Line(start, previousIntersect, self.toTrim:layer()))
        else
            b:append(Line(start, previousIntersect, self.toTrim:layer()))
            b:append(Line(nextIntersect, finish, self.toTrim:layer()))
        end
    end

    b:execute()

    self:close()
end

function TrimOperation:close()
    if(not self.finished) then
        self.finished = true

        event.delete("point", self)
        event.delete("selectionChanged", self)

        event.trigger('operationFinished')
    end
end